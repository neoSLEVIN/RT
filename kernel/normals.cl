

float3 sphere_normal(float3 hitpoint, float3 position) {
	float3 normal;
	normal = normalize(hitpoint - position);
	return normal;
}

float3 plane_normal(float3 planeDir, float3 rayDir) {
	float3 normal;
	float d;
	normal = planeDir;
	d = dot(rayDir, normal);
	return normal;
}

float3 box_normal(t_object *hit_obj, t_ray *ray) {
	float3	plane_dir;
	if (ray->index < 2)
		plane_dir = hit_obj->transform.direction;
	else if (ray->index < 4)
		plane_dir = normalize(cross(hit_obj->transform.direction, hit_obj->transform.rotation));
	else
		plane_dir = hit_obj->transform.rotation;
	return plane_normal(plane_dir, ray->dir);
}

float3 capsule_normal(t_object *hit_obj, t_ray *ray) {
	if (ray->index == 0)
		return cyl_normal(hit_obj, ray);
	else if (ray->index == 1)
		return sphere_normal(ray->hitPoint, hit_obj->transform.position + hit_obj->transform.direction * hit_obj->params.y / 2);
	return sphere_normal(ray->hitPoint, hit_obj->transform.position - hit_obj->transform.direction * hit_obj->params.y / 2);
}

float3 cyl_normal(t_object *hit_obj, t_ray *ray) {
	float	m;
	float3	x;
	float3	tmp[3];
	float3	normal;

	x = ray->origin - hit_obj->transform.position;
	m = dot(ray->dir, hit_obj->transform.direction) * ray->t + dot(x, hit_obj->transform.direction);
	tmp[0] = ray->hitPoint - hit_obj->transform.position;
	tmp[1] = hit_obj->transform.direction * m;
	tmp[2] = tmp[0] - tmp[1];
	normal = normalize(tmp[2]);
	return normal;
}

float3 cone_normal(t_object *hit_obj, t_ray *ray) {
	float	k;
	float	m;
	float3	tmp[8];
	float3	normal;

	k = tan(hit_obj->params.x);
	tmp[0] = ray->origin - hit_obj->transform.position;
	m = dot(ray->dir, hit_obj->transform.direction) * ray->t + dot(tmp[0], hit_obj->transform.direction);
	tmp[1] = ray->hitPoint - hit_obj->transform.position;
	tmp[2] = hit_obj->transform.direction * m;
	tmp[3] = tmp[1] - tmp[2];
	tmp[4] = hit_obj->transform.direction * m;
	tmp[5] = tmp[4] * k;
	tmp[6] = tmp[5] * k;
	tmp[7] = tmp[3] - tmp[6];
	normal = normalize(tmp[7]);
	return normal;
}

float3 capped_cone_normal(t_object *hit_obj, t_ray *ray) {
	float3	plane_dir;
	if (ray->index == 0)
		return cone_normal(hit_obj, ray);
	else if (ray->index == 1)
		plane_dir = hit_obj->transform.direction;
	else
		plane_dir = -hit_obj->transform.direction;
	return plane_normal(plane_dir, ray->dir);
}

int	is_outside_capped_cylinder(t_ray *ray, t_object *capped_cylinder, float value)
{
	return (pow(length(capped_cylinder->transform.position - (ray->origin + value * ray->dir)), 2) > (pow((capped_cylinder->params.y / 2.0f), 2) + pow(capped_cylinder->params.x, 2)));
}

float3 capped_cylinder_normal(t_object *capped_cylinder, t_ray *ray)
{
	/*Скалярное произведение вектора (из двух точек на крышке и в центре крышки) и dir равно 0. Однако с флотами есть погрешность*/
	float3 centerTop = capped_cylinder->transform.position + capped_cylinder->transform.direction * (capped_cylinder->params.y / 2.0f);
	float3 centerBottom = capped_cylinder->transform.position - capped_cylinder->transform.direction * (capped_cylinder->params.y / 2.0f);
	if (fabs(dot(centerTop - ray->hitPoint, capped_cylinder->transform.direction)) < 0.01f) {
		return plane_normal(capped_cylinder->transform.direction, ray->dir);
	} else if (fabs(dot(centerBottom - ray->hitPoint, capped_cylinder->transform.direction)) < 0.01f) {
		return plane_normal(capped_cylinder->transform.direction, ray->dir);
	}
	return cyl_normal(capped_cylinder, ray);
}

float3 triangle_normal(t_object *hit_obj)
{
	float3 v[2];

	v[0] = hit_obj->transform.dots[1] - hit_obj->transform.dots[0];
	v[1] = hit_obj->transform.dots[2] - hit_obj->transform.dots[1];
	return (normalize(cross(v[0], v[1])));
}

float3 apply_normal_map(t_object *hit_obj, t_ray *ray, float3 normal, t_scene *scene, int id) {
	
	float2 uv;
	float3 new_normal;
	float3 result_norm;
	
	ray->hitNormal = normal;
	
	uv = get_uv(hit_obj, ray, 10);
	new_normal = image_texture(uv, scene->normal_maps, id);
	new_normal.x = new_normal.x * 2.0f - 1.0f;
	new_normal.y = new_normal.y * 2.0f - 1.0f;
	new_normal.z = new_normal.z * 2.0f - 1.0f;
	
	result_norm = normal * new_normal.z + uv.x * new_normal.x + uv.y * new_normal.y;
	result_norm = normalize(result_norm);
	return result_norm;
}

float3 get_normal(t_object *hit_obj, t_ray *ray, t_scene *scene) {
	float3 normal = 0;

	switch (hit_obj->type)
	{
		case SPHERE:
			normal = sphere_normal(ray->hitPoint, hit_obj->transform.position);
			break;
		case CAPPEDPLANE:
		case CIRCLE:
		case PLANE:
			normal = plane_normal(hit_obj->transform.direction, ray->dir);
			break;
		case CYLINDER:
			normal = cyl_normal(hit_obj, ray);
			break;
		case CONE:
			normal = cone_normal(hit_obj, ray);
			break;
		case CAPPEDCONE:
			normal = capped_cone_normal(hit_obj, ray);
			break;
		case CAPSULE:
			normal = capsule_normal(hit_obj, ray);
			break;
		case CAPPEDCYLINDER:
			normal = capped_cylinder_normal(hit_obj, ray);
			break;
		case BOX:
			normal = box_normal(hit_obj, ray);
			break;
		case TRIANGLE:
		case OFF:
			normal = triangle_normal(hit_obj);
			break;
		case NONE:
			break;
	}
	if (hit_obj->normal_map.id >= 0) {
		normal = apply_normal_map(hit_obj, ray, normal, scene, hit_obj->normal_map.id);
	}
	/*Уже после наложения normal map мы исправляем нормаль для корректного отбражения света*/
	float d = dot(ray->dir, normal);
	if (d > 0)
		normal = normal * (-1.0f);
	return normal;
}
