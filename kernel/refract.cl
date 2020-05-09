/*Преломление*/

float3 go_refract(t_ray ray, __global t_object *objects, int num_obj, __global t_light *lights, int num_light) {
	
	float3 finalColor = 0;
	
	
	finalColor = continue_refract_ray(&ray, objects, num_obj, lights, num_light);
	
	if (objects[ray.hit_id].material.transparency == 0 && objects[ray.hit_id].material.reflective == 0) {
		return finalColor;
	}
	
	float ref = objects[ray.hit_id].material.reflective;
	if (ref > 0) {
		finalColor = finalColor * (1.0f - ref) + go_reflect(ray, objects, num_obj, lights, num_light) * ref;
	}
	
	/*объект обладает прозрачностью*/
	float trans = objects[ray.hit_id].material.transparency;
	if (trans > 0) {
		finalColor = finalColor * (1.0f - trans) + continue_refract_ray(&ray, objects, num_obj, lights, num_light) * trans;
	}
	
	return finalColor;
}

float3 continue_refract_ray(t_ray *ray, __global t_object *objects, int num_obj, __global t_light *lights, int num_light) {
	
	int maxBounds = 3;
	int oldHit_id = ray->hit_id;
	
	while (oldHit_id == ray->hit_id && maxBounds != 0) {
		ray->dir = refract(ray);
		ray->origin = ray->hitPoint + ray->dir * 0.1f;

		if (!is_intersect(ray, objects, num_obj, &(ray->hit_id), &(ray->t))) {
			break;
		}
		
		t_object obj = objects[ray->hit_id];
		ray->hitPoint = ray->origin + ray->t * ray->dir;
		ray->hitNormal = get_normal(&obj, ray);
		maxBounds--;
	}
	
	float3 trans_color = 0;
	if (ray->hit_id > 0) {
		t_object obj = objects[ray->hit_id];
		trans_color = get_obj_color(&(obj), ray) * get_light_intensity(ray, objects, num_obj, lights, num_light);
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
