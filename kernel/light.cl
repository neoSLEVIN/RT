
float get_light_intensity(t_ray *ray, t_scene *scene) {
	float totalLight = 0;
	
	for (int i = 0; i < scene->num_light; i++) {
		
		t_light light = scene->lights[i];
		
		switch (scene->lights[i].type) {
			case AMBIENT:
				totalLight += scene->lights[i].intensity;
				break;
			case POINT:
				totalLight += get_point_light(&light, ray, scene);
				break;
			case DIRECTION:
				totalLight += get_dir_light(&light, ray, scene);
				break;
			case CNT_OF_TYPES_L:
				break;
		}
	}
	if (totalLight >= 1.0f)
		totalLight = 1.0f;
	return totalLight;
}

float get_point_light(t_light *light, t_ray *ray, t_scene *scene) {
	float totalLight = 0.0f;
	float transparent_coef = 1.0f;
	
	if (!is_in_shadow_point(light, ray, scene, &transparent_coef)) {
/*		if (ray->hit_id < 0)
			printf("%d ", ray->hit_id);*/
		float specular = scene->objects[ray->hit_id].material.specular;
		totalLight = diffuse_light(light, ray, specular) * transparent_coef;
	}
	return totalLight;
}

/*при direction не считаем specular*/
float get_dir_light(t_light *light, t_ray *ray, t_scene *scene) {
	float totalLight = 0.0f;
	float transparent_coef = 1.0f;
	float3 light_dir = -light->direction;
	
	if (!is_in_shadow_directional(light, ray, scene, &transparent_coef)) {
		float power = dot(ray->hitNormal, light_dir);
		if (power < 0.0f)
			power = 0.0f;
		totalLight = power * light->intensity * transparent_coef;
	}
	return totalLight;
}


bool is_in_shadow_directional(t_light *light, t_ray *ray, t_scene *scene, float *transparent_coef) {
	t_ray light_ray;
	t_transparent_obj tmp;
	
	/*тут будет ближайший прозрачный объект*/
	tmp.t = MY_INFINITY;
	tmp.hit_id = -1;
	
	/*чтобы не было пересечения с самим собой двигаем немного по нормали*/
	light_ray.origin = ray->hitPoint + ray->hitNormal * 0.01f;
	light_ray.dir = -light->direction;
	if (scene->objects[ray->hit_id].material.transparency > 0) {
		is_intersect(&light_ray, scene, 0);
	} else {
		is_intersect(&light_ray, scene, &tmp);
	}
	if (light_ray.hit_id >= 0) {
		return 1;
	} else if (tmp.hit_id >= 0) {
		*transparent_coef = scene->objects[tmp.hit_id].material.transparency;
		return 0;
	}
	
	return 0;
}

bool is_in_shadow_point(t_light *light, t_ray *ray, t_scene *scene, float *transparent_coef) {
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
	/*более-менее оптимальное значение 0.999 - больше и на мелких объектах вдали артефакты
	 меньше и луч света проникает на стыках*/
	if (light_ray.t < dist * 0.999) {
		return (1);
	}
	/*теперь у нас есть пересечение с прозрачным объектом на пути к непрозрачному*/
	if (tmp.t < light_ray.t && tmp.hit_id >= 0) {
		*transparent_coef = scene->objects[tmp.hit_id].material.transparency;
	}
	return (0);
}

float	diffuse_light(t_light *light, t_ray *ray, float specular) {
	float res;
	float angle;
	float3 light_vect;

	res = 0;
	light_vect = light->position - ray->hitPoint;
	angle = dot(ray->hitNormal, light_vect);

	if (angle > 0.0f)
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

float	compute_specular(float3 normal_to_intersect, float3 light_vector, float3 rayDir, float object_specular)
{
	float n = 0;
	float3 R = 2.0f * normal_to_intersect * dot(normal_to_intersect, light_vector) - light_vector;
	float r_dot_v = dot(R, rayDir);
	if (r_dot_v > 0.0f) {
		float tmp = length(R) * length(rayDir);
		n = pow( r_dot_v / tmp, 1.0f / object_specular);
	}
	/*некорректно отображается в отражении поэтому убираю отрицательные значения. хз как решить пока*/
	return fmax(0.0f,n);
}
