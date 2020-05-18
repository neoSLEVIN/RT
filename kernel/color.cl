
float3 get_obj_color(t_object *obj, t_ray *ray) {
	float3 color;
/*	if (obj->marker)
		return (float3)(0.8f, 0.8f, 0.8f);*/
	if (obj->type == PLANE) {
		
		/*
		float2 uv = plane_map(obj, ray, 10);
		return uv_patter_plane_lines_cross(uv);
		*/
		 
		return plane_lines_cross(obj, ray);
		
	} else if (obj->type == SPHERE) {
		
		float2 uv = sphere_map(obj, ray);
		return typical_noise(obj, uv, 30);
		return wood(obj, uv, 1);
		
	} else if (obj->type == CONE) {
		
		float2 uv = cylindrical_map(obj, ray, 2);
		return uv_patter_lines(uv);
		
		
	} else if (obj->type == CYLINDER) {
		
		float2 uv = cylindrical_map(obj, ray, 10);
		return uv_patter_checker(8, 8, uv);
	}
	
	return obj->material.color;
}

char convertColorFromFloat(float f) {
	return floor(f >= 1.0 ? 255 : f * 256.0);
}
