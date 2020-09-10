

float3 send_ray(t_ray *ray, t_scene *scene) {

	float3 backColor = 0;
	float intensity;
	float3 resColor = 0;

	if (!is_intersect(ray, scene, 0))
		return backColor;
/*	if (ray->hit_id < 0)
		printf("%d ", ray->hit_id);*/
	t_object hit_obj = scene->objects[ray->hit_id];
	if (hit_obj.type == OFF)
	{
		reinit_off_obj(&hit_obj, scene, ray);
	}
	intensity = get_light_intensity(ray, scene);
	resColor = get_obj_color(&hit_obj, ray, scene);
	resColor =  resColor * intensity;
	return resColor;
}

void init_ray(t_ray *ray, CAMERA *cam, int work_id, float rand)
{

	ray->origin = cam->origin;
	float x = work_id % cam->max_screen.x - cam->diff_screen.x;
	float y = work_id / cam->max_screen.x - cam->diff_screen.y;
	float2 coord = (float2)(x + rand, y + rand );

	float2 viewport_coordinate;
	viewport_coordinate.x = ((2.0 * coord.x) / cam->screen_w) - 1;
	viewport_coordinate.y = ((-2.0 * coord.y) / cam->screen_h) + 1;

	float pixel_half = cam->viewport_w / cam->screen_w;
	ray->dir = cam->right * (viewport_coordinate.x * cam->viewport_w - pixel_half);
	ray->dir += cam->up * (viewport_coordinate.y * cam->viewport_h - pixel_half);
	ray->dir += cam->forward;
	ray->dir = normalize(ray->dir);
	ray->hit_id = -1;
	ray->index = -1;
}
