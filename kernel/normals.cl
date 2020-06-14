

float3 sphere_normal(float3 hitpoint, float3 position, float3 rayDir) {
	float3 normal;
	normal = normalize(hitpoint - position);
	/*
	return dot(rayDir, normal) < 0.0f ? normal : normal * (-1.0f);
	*/
	return normal;
}

float3 plane_normal(float3 planeDir, float3 rayDir) {
	float3 normal;
	float d;
	normal = planeDir;
	d = dot(rayDir, normal);
	if (d > 0)
		normal = normal * (-1.0f);
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

	k = tan(hit_obj->radius);
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

float3 capped_cylinder_normal(t_object *hit_obj, t_ray *ray)
{
	float3 abc[2];
    float tmp[7];
    float t;
    float y;
	float3 rarb[2];

	rarb[0] = hit_obj->transform.position - hit_obj->transform.direction * hit_obj->radius;
    rarb[1] = hit_obj->transform.position + hit_obj->transform.direction * hit_obj->radius;
    abc[0] = rarb[1] - rarb[0];/*ca*/
    abc[1] = ray->origin - rarb[0]; /*oc*/
    tmp[0] = dot(abc[0], abc[0]); 	/*caca*/
    tmp[1] = dot(abc[0], ray->dir); /*card*/
    tmp[2] = dot(abc[0], abc[1]);	/*caoc*/
    tmp[3] = tmp[0] - pow(tmp[1], 2); /*a*/
    tmp[4] = tmp[0] * dot(abc[1], ray->dir) - tmp[2] * tmp[1]; /*b*/
    tmp[5] = tmp[0] * dot(abc[1], abc[1]) - pow(tmp[2], 2) - pow(hit_obj->radius, 2) * tmp[0];/*c*/
    tmp[6] = pow(tmp[4], 2) - tmp[3] * tmp[5]; /*h*/
    tmp[6] = sqrt(tmp[6]);
    t = (-tmp[4] - tmp[6]) / tmp[3];
    y = tmp[2] + t * tmp[1];
    if (y > 0.0f && y < tmp[0])
    	return ((abc[1] + t * ray->origin - abc[0] * y / tmp[0]) / hit_obj->radius);
    t = (((y < 0.0) ? 0.0 : tmp[0]) - tmp[2]) / tmp[1];
    return abc[0] * sign(y) / tmp[0];
}

float3 ellipsoid_normal(t_object *hit_obj, t_ray *ray)
{
	float3 param;
	param.x = 2;
	param.y = 1;
	param.z = 3;
	return (normalize((ray->hitPoint - hit_obj->transform.position) / param));
}

float3	ellipse_normal(t_object *hit_obj, t_ray *ray)
{
	float3 radius[2];
	float3 r;

	r.x = 3;
    r.y = 1;
    r.z = 1;
    radius[0] = hit_obj->transform.position + hit_obj->transform.direction * hit_obj->radius;
    radius[1] = hit_obj->transform.position + r * hit_obj->radius;
    return (normalize(cross(radius[0], radius[1])));
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
		case ELLIPSOID:
			normal = ellipsoid_normal(hit_obj, ray);
			break;
		case ELLIPSE:
			normal = ellipse_normal(hit_obj, ray);
			break;
	}
	if (hit_obj->normal_map.id >= 0) {
		normal = apply_normal_map(hit_obj, ray, normal, scene, hit_obj->normal_map.id);
	}
	return normal;
}
