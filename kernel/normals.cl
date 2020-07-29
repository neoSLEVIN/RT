

float3 sphere_normal(float3 hitpoint, float3 position, float3 rayDir) {
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

int	is_outside_capped_cylinder(t_ray *ray, t_object *capped_cylinder, float value)
{
	return (pow(length(capped_cylinder->transform.position - (ray->origin + value * ray->dir)), 2) > (pow((capped_cylinder->params.y / 2.0f), 2) + pow(capped_cylinder->params.x, 2)));
}

float3 capped_cylinder_normal(t_object *capped_cylinder, t_ray *ray)
{
	float		abcd[4];
	float		t[4] = {-1.0f, -1.0f, -1.0f, -1.0f};
	float3		x;
	float		d_dot_n;

	x = ray->origin - capped_cylinder->transform.position;
	abcd[0] = dot(ray->dir, ray->dir) - pow(dot(ray->dir, capped_cylinder->transform.direction), 2);
	abcd[1] = 2 * (dot(ray->dir, x) - (dot(ray->dir, capped_cylinder->transform.direction) * dot(x, capped_cylinder->transform.direction)));
	abcd[2] = dot(x, x) - pow(dot(x, capped_cylinder->transform.direction), 2) - capped_cylinder->params.x * capped_cylinder->params.x;
	abcd[3] = pow(abcd[1], 2) - 4 * abcd[0] * abcd[2];
	if (abcd[3] >= 0) {
		t[0] = (-abcd[1] + sqrt(abcd[3])) / (2 * abcd[0]);
		t[1] = (-abcd[1] - sqrt(abcd[3])) / (2 * abcd[0]);
		if (is_outside_capped_cylinder(ray, capped_cylinder, t[0]))
			t[0] = -1.0f;
		if (is_outside_capped_cylinder(ray, capped_cylinder, t[1]))
			t[1] = -1.0f;
	}

	x = capped_cylinder->transform.position + capped_cylinder->transform.direction * capped_cylinder->params.y / 2.0f - ray->origin;
	if ((d_dot_n = dot(ray->dir, capped_cylinder->transform.direction)) != 0.0f) {
		t[2] = dot(x, capped_cylinder->transform.direction) / d_dot_n;
		if (is_outside_capped_cylinder(ray, capped_cylinder, t[2]))
			t[2] = -1.0f;
	}

	x = capped_cylinder->transform.position - capped_cylinder->transform.direction * capped_cylinder->params.y / 2.0f - ray->origin;
	if ((d_dot_n = dot(ray->dir, -capped_cylinder->transform.direction)) != 0.0f) {
		t[3] = dot(x, -capped_cylinder->transform.direction) / d_dot_n;
		if (is_outside_capped_cylinder(ray, capped_cylinder, t[3]))
			t[3] = -1.0f;
	}

	if (minT(t[0], t[1]) <= 0.0f)
	{
		if (t[2] <= t[3] && t[2] > 0.0f) {
			return plane_normal(capped_cylinder->transform.direction, ray->dir);
		} else {
			return plane_normal(-capped_cylinder->transform.direction, ray->dir);
		}
	} else if (minT(t[2], t[3]) <= 0.0f) {
		return (cyl_normal(capped_cylinder, ray));
	} else if (minT(t[0], t[1]) <= minT(t[2], t[3])) {
		return (cyl_normal(capped_cylinder, ray));
	} else {
		if (t[2] <= t[3] && t[2] > 0.0f) {
			return plane_normal(capped_cylinder->transform.direction, ray->dir);
		} else {
			return plane_normal(-capped_cylinder->transform.direction, ray->dir);
		}
	}

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
			normal = sphere_normal(ray->hitPoint, hit_obj->transform.position, ray->dir);
			break;
		case PLANE:
			normal = plane_normal(hit_obj->transform.direction, ray->dir);
			break;
		case CYLINDER:
			normal = cyl_normal(hit_obj, ray);
			break;
		case CONE:
			normal = cone_normal(hit_obj, ray);
			break;
		case CAPPEDCYLINDER:
        	normal = capped_cylinder_normal(hit_obj, ray);
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
