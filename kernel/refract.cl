/*Преломление*/

float3 go_refract(t_ray ray, t_scene *scene) {
	
	float3 finalColor = 0;
	
	finalColor = continue_refract_ray(&ray, scene);
	
	if (scene->objects[ray.hit_id].material.transparency == 0 && scene->objects[ray.hit_id].material.reflective == 0) {
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
		ray->dir = refract(ray);
		ray->origin = ray->hitPoint + ray->dir * 0.1f;

		if (!is_intersect(ray, scene->objects, scene->num_obj, &(ray->hit_id), &(ray->t))) {
			break;
		}
		
		t_object obj = scene->objects[ray->hit_id];
		ray->hitPoint = ray->origin + ray->t * ray->dir;
		ray->hitNormal = get_normal(&obj, ray);
		maxBounds--;
	}
	
	float3 trans_color = 0;
	if (ray->hit_id > 0) {
		t_object obj = scene->objects[ray->hit_id];
		trans_color = get_obj_color(&(obj), ray, scene) * get_light_intensity(ray, scene);
	}
	return trans_color;
}

float3 refract(t_ray *ray) {
	/*cтепень преломления - воздух - 1 стекло - 1.5*/
	float ior = 1.0f;
	float eta;
	float3 hitNormal = ray->hitNormal;
	bool inside = dot(ray->dir, hitNormal) > 0;
	if (inside) {
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
