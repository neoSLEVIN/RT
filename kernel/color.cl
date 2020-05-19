
float3 image_texture(float2 uv, __global char *texture)  {
	
	float3 res = 0;
	
	int nx = 640;
	int ny = 640;
	
	int i = uv.x * nx;
	int j = uv.y * ny - 0.001;
	
	
	if (i < 0)
		i = 0;
	if (j < 0)
		j = 0;

	if (i > nx - 1)
		i = nx - 1;
	if (j > ny - 1)
		j = ny - 1;
	 
	int position = j * 640 + i;
	float r = int(texture[position * 3]  ) / 255.0;
	float g = int(texture[position * 3 + 1]) / 255.0;
	float b = int(texture[position * 3 + 2]) / 255.0;
	
	res = (float3)(r,g,b);
	
	return res;
}




float3 get_obj_color(t_object *obj, t_ray *ray, t_scene *scene) {
	float3 color;
	if (obj->marker)
		return (float3)(0.8f, 0.8f, 0.8f);
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
