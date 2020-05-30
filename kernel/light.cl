
float get_light_intensity(t_ray *ray, t_scene *scene) {
	float totalLight = 0;
	float light_intensity = 1;
	int i = 0;
	while (i < scene->num_light) {
		if (scene->lights[i].type == AMBIENT) {
			totalLight += scene->lights[i].intensity;
		} else if (scene->lights[i].type == POINT) {
			t_light light = scene->lights[i];
			if (!is_in_shadow(&light, ray, scene, &light_intensity)) {
				int specular = scene->objects[ray->hit_id].material.specular;
				totalLight += diffuse_light(&light, ray, specular) * light_intensity;
			}

		}
		i++;
	}
	return totalLight;
}

bool is_in_shadow(t_light *light, t_ray *ray, t_scene *scene, float *light_intensity) {
	float dist;
	t_transparent_obj tmp;
	t_ray light_ray;
	
	/*тут будет ближайший прозрачный объект*/
	tmp.t = MY_INFINITY;
	tmp.hit_id = -1;
	
	dist = length(light->position - ray->hitPoint);
	light_ray.origin = light->position;
	light_ray.dir = normalize(ray->hitPoint - light->position);
	/*Если мы луч изначально попал в прозрачный объект, считает количество света как обычно*/
	/*В противном случаем учитываем прозрачные объекты*/
	if (scene->objects[ray->hit_id].material.transparency > 0) {
		is_intersect(&light_ray, scene, 0);
	} else {
		is_intersect(&light_ray, scene, &tmp);
	}
	/*Нашли непрозрачный объект дистация до которого меньше - есть тень*/
	if (light_ray.t < dist - 0.01) {
		return (1);
	}
	
	/*теперь у нас есть пересечение с прозрачным объектом на пути к непрозрачному*/
	if (tmp.t < light_ray.t) {
		*light_intensity = scene->objects[tmp.hit_id].material.transparency;
	}
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
