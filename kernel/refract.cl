/*Преломление*/

float3 go_refract(t_ray ray, t_scene *scene) {
	
	float3 finalColor = 0;

	finalColor = continue_refract_ray(&ray, scene);
	if (ray.hit_id < 0) {
		return finalColor;
	}
	if (scene->objects[ray.hit_id].material.transparency == 0 &&
		scene->objects[ray.hit_id].material.reflective == 0) {
		return finalColor;
	}

	float ref = scene->objects[ray.hit_id].material.reflective;
	if (ref > 0) {
		finalColor = finalColor * (1.0f - ref) + go_reflect(ray, scene) * ref;
	}

	/*объект обладает прозрачностью*/
	float trans = scene->objects[ray.hit_id].material.transparency;
	if (trans > 0) {
		finalColor = finalColor * (1.0f - trans) + continue_refract_ray(&ray, scene) * trans;
	}

	return finalColor;
}

float3 continue_refract_ray(t_ray *ray, t_scene *scene) {
	
	int maxBounds = 3;
	int oldHit_id = ray->hit_id;

	while (oldHit_id == ray->hit_id && maxBounds != 0) {
		ray->origin = ray->hitPoint + ray->dir * 0.002f;
		float degree;
		if (ray->hit_id < 0)
			degree = 0.0f;
		else
			degree = scene->objects[ray->hit_id].material.degree_of_refraction;
		ray->dir = refract(ray, degree);

		if (!is_intersect(ray, scene, 0)) {
			break;
		}
		maxBounds--;
	}
	
	float3 trans_color = 0;
	if (ray->hit_id >= 0) {
		t_object obj = scene->objects[ray->hit_id];
		if (obj.type == OFF)
		{
			reinit_off_obj(&obj, scene, ray);
		}
		trans_color = get_obj_color(&(obj), ray, scene);
		trans_color = trans_color * get_light_intensity(ray, scene);
	}
	return trans_color;
}


/*
 Текущая версия
 Взято отсюда https://graphics.stanford.edu/courses/cs148-10-summer/docs/2006--degreve--reflection_refraction.pdf
 и модифицирована чутка
 а нашел через https://stackoverflow.com/questions/29758545/how-to-find-refraction-vector-from-incoming-vector-and-surface-normal
 */
float3 refract(t_ray *ray, float degree) {
	/*cтепень преломления - воздух - 1 стекло - 1.5*/
	float ior = 1.0f + degree / 2;
	float eta;
	
	float3 hitNormal = ray->hitNormal;
	bool inside = dot(ray->dir, hitNormal) > 0;
	
	/*Добавлено так как мы проходим через объект два раза. Но не для плоскости*/
	if (inside && (ray->hit_type != PLANE && ray->hit_type != CAPPEDPLANE &&
			ray->hit_type != CIRCLE && ray->hit_type != TRIANGLE && ray->hit_type != OFF)) {
		hitNormal = -hitNormal;
		eta = ior;
	} else {
		eta = 1.0f / ior;
	}
	
	float cosI = - dot(hitNormal, ray->dir);
	float sinT2 = eta * eta * (1.0f - cosI * cosI);
	if (sinT2 > 1.0f)
		return ray->dir;
	float cosT = sqrt(1.0f - sinT2);
	return eta * ray->dir + (eta * cosI - cosT) * hitNormal;
	
}


/*
 Взят отсюда
 https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-ray-tracing/ray-tracing-practical-example
 но проблемы при с specular светом когда смотришь на объект через прозрачную PLANE
 */
float3 refract_v1(t_ray *ray) {
	/*cтепень преломления - воздух - 1 стекло - 1.5*/
	float ior = 1.0f;
	float eta;
	float3 hitNormal = ray->hitNormal;
	bool inside = dot(ray->dir, hitNormal) > 0;
	if (inside && (ray->hit_type != PLANE && ray->hit_type != CAPPEDPLANE && ray->hit_type != CIRCLE && ray->hit_type != TRIANGLE)) {
		hitNormal = -hitNormal;
		eta = ior;
	} else {
		eta = 1.0f / ior;
	}
	
	float cosi = dot(-hitNormal, ray->dir);
	float k = 1 - eta * eta * (1.0f - cosi * cosi);

	float3 refDir = ray->dir * eta + hitNormal * (eta * cosi - sqrt(k));
	refDir = normalize(refDir);
	return refDir;
}


/*
 тоже работает
 Но вроде не до конца
 https://stackoverflow.com/questions/42218704/how-to-properly-handle-refraction-in-raytracing
 */
float3 refract1(t_ray *ray) {
	
	float ior = 1.0f;
	float eta = 2.0f - ior;
	float cosi = dot(ray->hitNormal, ray->dir);
	float3 o = (ray->dir * eta - ray->hitNormal * (-cosi + eta * cosi));
	return o;
}
