

float3 compute_color(t_scene *scene, t_ray *ray) {
	float3 finalColor = 0;
	
	float3 tmpColor = send_ray(ray, scene);
	if (ray->hit_id >= 0) {
		float ref = scene->objects[ray->hit_id].material.reflective;
		float trans;

		trans = scene->objects[ray->hit_id].material.transparency;

		if (ref == 0 && trans == 0)
			return tmpColor;
/*		if (ref > 0)
			finalColor = tmpColor * (1.0f - ref) + go_reflect(*ray, scene) * ref;
		if (trans > 0)
			finalColor = tmpColor * (1.0f - trans) + go_refract(*ray, scene) * trans;*/
		float3 reflect_color = 0;
		float3 refract_color = 0;
		if (ref > 0)
			reflect_color = go_reflect(*ray, scene);
		if (trans > 0)
			refract_color = go_refract(*ray, scene);
		finalColor = tmpColor * (1.0f - ref) + reflect_color * ref;
		finalColor = finalColor * (1.0f - trans) + refract_color * trans;
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
				__global t_ppm_image *normal_maps,
				int mirror,
				__global float3 *points,
				__global int3 *faces,
				__global float3 *colors,
				int point_cnt,
				int faces_cnt)
{
	scene->objects = objects;
	scene->num_obj = num_obj;
	scene->lights = lights;
	scene->num_light = num_light;
	scene->cam = cam;
	scene->seed = seed;
	scene->textures = textures;
	scene->normal_maps = normal_maps;
	scene->mirror = mirror;
	scene->points = points;
	scene->faces = faces;
	scene->colors = colors;
	scene->point_cnt = point_cnt;
	scene->faces_cnt = faces_cnt;
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
							FILTER filter,
							__global int *output_id,
							float3 filter_params,
							int anti_aliasing,
							int mirror,
							__global float3 *points,
							__global int3 *faces,
							__global float3 *colors,
							int point_cnt,
							int faces_cnt)
{
	const int work_item_id = get_global_id(0);
	uint seed = seedsInput[work_item_id];
	if (work_item_id / cam.max_screen.x > cam.screen_h + cam.diff_screen.y ||
		work_item_id / cam.max_screen.x < cam.diff_screen.y ||
		work_item_id % cam.max_screen.x > cam.screen_w + cam.diff_screen.x ||
		work_item_id % cam.max_screen.x < cam.diff_screen.x)
	{
		output[work_item_id] = (char4)(255, 255, 255, 0);
		if (work_item_id == cursor.y * cam.max_screen.x + cursor.x)
			output_id[0] = -1;
		seedsInput[work_item_id] = seed;
	}
	else
	{
		float3 finalColor = 0;
		t_ray ray;
		t_scene scene;

		/*Набор случайных чисел*/
		init_scene(&scene, objects, num_obj, lights, num_light, cam, seed,
					textures, normal_maps, mirror, points, faces, colors, point_cnt, faces_cnt);

		int xQuality = anti_aliasing ? 4 : 1;
		/*Сглаживание*/
		for (int i = 0; i < xQuality; i++) {
			/* разброс [-0.5,0.5] а стреляем из центра пикселя*/
			float rnd = xQuality > 1 ? ((2 * get_random(&seed) - 1) / 2) : 0;
			init_ray(&ray, &cam, work_item_id, rnd);
			finalColor += compute_color(&scene, &ray);
		}
		finalColor /= (float)xQuality;

		if (filter != NO_FILTER)
			apply_filter(&finalColor, filter, filter_params);

		char red = convertColorFromFloat(finalColor.x);
		char green = convertColorFromFloat(finalColor.y);
		char blue = convertColorFromFloat(finalColor.z);

		char alfa = 255;

		output[work_item_id] = (char4)(red, green, blue, alfa);


		if (work_item_id == cursor.y * cam.max_screen.x + cursor.x)
			output_id[0] = ray.hit_id;
		seedsInput[work_item_id] = seed;
	}
}
