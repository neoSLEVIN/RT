

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

float3 get_normal(t_object *hit_obj, t_ray *ray) {
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
	}
	return normal;
}
