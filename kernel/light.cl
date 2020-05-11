
float get_light_intensity(t_ray *ray, __global t_object *obj, int num_obj, __global t_light *lights, int num_light) {
	float totalLight = 0;
	int i = 0;
	while (i < num_light) {
		if (lights[i].type == AMBIENT) {
			totalLight += lights[i].intensity;
		} else if (lights[i].type == POINT) {
			t_light light = lights[i];
			if (!is_in_shadow(&light, ray, obj, num_obj)) {
				int specular = obj[ray->hit_id].material.specular;
				totalLight += diffuse_light(&light, ray, specular);
			}

		}
		i++;
	}
	return totalLight;
}

bool is_in_shadow(t_light *light, t_ray *ray, __global t_object *obj, int num_obj) {
	float dist;
	float t;
	int hit_id;

	t_ray light_ray;
	dist = length(light->position - ray->hitPoint);
	light_ray.origin = light->position;
	light_ray.dir = normalize(ray->hitPoint - light->position);
	is_intersect(&light_ray, obj, num_obj, &hit_id, &t);
	if (t < dist - 0.01)
		return (1);
	return (0);
}

float	diffuse_light(t_light *light, t_ray *ray, int specular) {
	float res;
	float angle;
	float3 light_vect;

	res = 0;
	light_vect = light->position - ray->hitPoint;
	angle = dot(ray->hitNormal, light_vect);

	if (angle > 0)
	{
		float tmp1 = light->intensity * angle;
		float tmp2 = length(ray->hitNormal) * length(light_vect);
		res += tmp1 / tmp2;
	}
	if (specular > 0)
	{
		float3 dir = normalize(ray->dir) * (-1.0f);
		float3 nor = ray->hitNormal;
		float b = compute_specular(nor, light_vect, dir, specular);
		res = res + (light->intensity * b);
	}
	return res;
}

float	compute_specular(float3 normal_to_intersect, float3 light_vector, float3 rayDir, int object_specular)
{
	float n = 0;
	float3 R = 2 * normal_to_intersect * dot(normal_to_intersect, light_vector) - light_vector;
	float r_dot_v = dot(R, rayDir);
	if (r_dot_v > 0) {
		float tmp = length(R) * length(rayDir);
		n = pow( r_dot_v / tmp, object_specular);
	}
	return n;
}