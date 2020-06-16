int filter_sepia(char *red, char *green, char *blue, int depth)
{
	char average;
	
	average = (*red + *green + *blue) / 3;
	
	*red = average + depth * 2;
	*green = average + depth;
	*blue = average;
	if (*red > 255)
		*red = 255;
	if (*green > 255)
		*green = 255;
	if (*blue > 255)
		*blue = 255;
	return (1);
}

int filter_negative(char *red, char *green, char *blue)
{
	*red = 255 - *red;
	*green = 255 - *green;
	*blue = 255 - *blue;
	return (2);
}

int filter_noise(char *red, char *green, char *blue, int noise)
{
	*red = *red + noise;
	if (*red < 0)
		*red = 0;
	if (*red > 255)
		*red = 255;
	*green = *green + noise;
	if (*green < 0)
		*green = 0;
	if (*green > 255)
		*green = 255;
	*blue = *blue + noise;
	if (*blue < 0)
		*blue = 0;
	if (*blue > 255)
		*blue = 255;
	
	return (3);
}

int filter_shades_of_gray(char *red, char *green, char *blue)
{
	char average;
	
	average = (*red + *green + *blue) / 3;
	*red = average;
	*green = average;
	*blue = average;
	return (4);
}

int apply_filter(char *red, char *green, char *blue, int filter)
{
	int depth_sepia = 30;
	int noise = 10;
	
	if (filter == 1)
		filter = filter_sepia(red, green, blue, depth_sepia);
	if (filter == 2)
		filter = filter_negative(&red, &green, &blue);
	if (filter == 3)
		filter = filter_noise(&red, &green, &blue, noise);
	if (filter == 4)
		filter = filter_shades_of_gray(&red, &green, &blue);
	
	return (filter);
}


float3 compute_color(t_scene *scene, t_ray *ray) {
	float3 finalColor = 0;
	
	float3 tmpColor = send_ray(ray, scene);
	if (ray->hit_id >= 0) {
		float ref = scene->objects[ray->hit_id].material.reflective;
		float trans;

		trans = scene->objects[ray->hit_id].material.transparency;

		if (ref == 0 && trans == 0)
			return tmpColor;;
		if (ref > 0)
			finalColor = tmpColor * (1.0f - ref) + go_reflect(*ray, scene) * ref;
		if (trans > 0)
			finalColor = tmpColor * (1.0f - trans) + go_refract(*ray, scene) * trans;
	}
	return finalColor;
}

void init_scene(t_scene *scene,
				__global t_object *objects,
				int num_obj,
				__global t_light *lights,
				int num_light,
				CAMERA cam,
				uint seed,
				__global t_ppm_image *textures,
				__global t_ppm_image *normal_maps)
{
	scene->objects = objects;
	scene->num_obj = num_obj;
	scene->lights = lights;
	scene->num_light = num_light;
	scene->cam = cam;
	scene->seed = seed;
	scene->textures = textures;
	scene->normal_maps = normal_maps;
}

__kernel void render_kernel(__global t_object *objects,
							int num_obj,
							__global t_light *lights,
							int num_light,
							CAMERA cam,
							__global char4* output,
							__global unsigned int *seedsInput,
							int2 cursor,
							__global t_ppm_image *textures,
							__global t_ppm_image *normal_maps,
							__global int *output_id)
{
	float3 finalColor = 0;
	t_ray ray;
	t_scene scene;
	const int work_item_id = get_global_id(0);
	/*Набор случайных чисел*/
	uint seed = seedsInput[work_item_id];
	init_scene(&scene, objects, num_obj, lights, num_light, cam, seed, textures, normal_maps);
	
	int xQuality = 1;
	/*Сглаживание*/
	for (int i = 0; i < xQuality; i++) {
		/* разброс [-0.5,0.5] а стреляем из центра пикселя*/
		float rnd = xQuality > 1 ? ((2 * get_random(&seed) - 1) / 2) : 0;
		init_ray(&ray, &cam, work_item_id, rnd);
		finalColor += compute_color(&scene, &ray);
	}
	finalColor /= (float)xQuality;

	char red = convertColorFromFloat(finalColor.x);
	char green = convertColorFromFloat(finalColor.y);
	char blue = convertColorFromFloat(finalColor.z);
	/*
	 filter = 1 - Сепия
	 filter = 2 - Негатив
	 filter = 3 - Шум
	 filter = 4 - Оттенки серого
	 */
	int filter = 1;
	if (filter > 0 && filter < 5)
		filter = apply_filter(&red, &green, &blue, filter);
	
	char alfa = 255;

	output[work_item_id] = (char4)(red, green, blue, alfa);
	
	/*тест для вывода первой картинки в левый верхний угол*/
	/*
 	int x = work_item_id % cam.screen_w;
 	int y = work_item_id / cam.screen_w;
 	if (x < 640 && y < 640) {
 		int i = y * 640 + x;
 		output[work_item_id] = (char4)(normal_maps->data[i * 3], normal_maps->data[i * 3 + 1], normal_maps->data[i * 3 + 2], alfa);
 	}
 	*/
	

	if (work_item_id == cursor.y * cam.screen_w + cursor.x)
		output_id[0] = ray.hit_id;
	seedsInput[work_item_id] = seed;
}
