
__kernel void render_kernel(__global t_object *objects,
							int num_obj,
							__global t_light *lights,
							int num_light,
							CAMERA cam,
							__global char4* output,
							__global unsigned int *seedsInput)
{
	float3 finalColor = 0;
	t_ray ray;
	const int work_item_id = get_global_id(0);
	/*Набор случайных чисел*/
	uint seed = seedsInput[work_item_id];


	/*Сглаживание*/
	for (int i = 0; i < 6; i++) {
		float rnd = (2 * get_random(&seed) - 1) / 2;
		init_ray(&ray, &cam, work_item_id, rnd);

		float3 finalColor1 = send_ray(&ray, objects, num_obj, lights, num_light);


		if (ray.hit_id >= 0) {
			float ref = objects[ray.hit_id].material.reflective;
			float trans = objects[ray.hit_id].material.transparency;
			
			if (ref == 0 && trans == 0) {
				finalColor += finalColor1;
			} else {
				
				if (ref > 0) {
					
					finalColor += finalColor1 * (1.0f - ref) + go_reflect(ray, objects, num_obj, lights, num_light) * ref;
					
				}
				
				if (trans > 0) {
					
					finalColor += finalColor1 * (1.0f - trans) + go_refract(ray, objects, num_obj, lights, num_light) * trans;

				}
				
			}
		}

	}
	finalColor /= 6.0f;


	char red = convertColorFromFloat(finalColor.x);
	char green = convertColorFromFloat(finalColor.y);
	char blue = convertColorFromFloat(finalColor.z);
	char alfa = 255;

	output[work_item_id] = (char4)(red, green, blue, alfa);

	seedsInput[work_item_id] = seed;
}
