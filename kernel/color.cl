
float3 image_texture(float2 uv, __global t_ppm_image *texture, int id)  {
	
	float3 res = 0;

	int nx = texture[id].width;
	int ny = texture[id].height;
	
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
	 
	int position = j * nx + i;
	float r = (int)(texture[id].data[position * 3]  ) / 255.0;
	float g = (int)(texture[id].data[position * 3 + 1]) / 255.0;
	float b = (int)(texture[id].data[position * 3 + 2]) / 255.0;
	
	res = (float3)(r,g,b);
	
	return res;
}

/*TODO вынести splits в текстуру*/
float2 get_uv(t_object *obj, t_ray *ray, int splits) {
	if (obj->type == PLANE || obj->type == CAPPEDPLANE || obj->type == CIRCLE || obj->type == TRIANGLE) {
		return plane_map(obj, ray, splits);
	} else if (obj->type == BOX) {
		return box_map(obj, ray, splits);
	} else if (obj->type == SPHERE) {
		return sphere_map(obj, ray);
	} else if (obj->type == CONE || obj->type == CYLINDER || obj->type == CAPSULE) {
		return cylindrical_map(obj, ray, splits);
	} else if (obj->type == CAPPEDCYLINDER) {
		return capped_cylindrical_map(obj, ray, splits);
	} else if (obj->type == CAPPEDCONE) {
		return capped_cone_map(obj, ray, splits);
	}
	/*по дефолту*/
	return sphere_map(obj, ray);
}


/*TODO*/
/*
 -разобраться с коэф. размера для uv и для текстуры
 по идее это должно задаваться для каждого объекта
 */
float3 get_obj_color(t_object *obj, t_ray *ray, t_scene *scene) {

	if (obj->texture.id == -1) {
		
		return obj->material.color;
		
	} else if (obj->texture.id >= 0) {
		
		float2 uv = get_uv(obj, ray, 10);
		return image_texture(uv, scene->textures, obj->texture.id);
		
	} else if (obj->texture.id == -2) {
		
		float2 uv = get_uv(obj, ray, 10);
		return wood(obj, uv, 1);
		
	} else if (obj->texture.id == -3) {
		
		float2 uv = get_uv(obj, ray, 10);
		return typical_noise(obj, uv, 10);
		
	} else if (obj->texture.id == -4) {
		
		float2 uv = get_uv(obj, ray, 10);
		return uv_patter_checker(8, 8, uv);
		
	} else if (obj->texture.id == -5) {
		
		float2 uv = get_uv(obj, ray, 4);
		return uv_patter_lines(uv);
	}
	
	
	return obj->material.color;
}

char convertColorFromFloat(float f) {
	if (f <= 0)
		return 0;
	return floor(f >= 1.0 ? 255 : f * 256.0);
}

