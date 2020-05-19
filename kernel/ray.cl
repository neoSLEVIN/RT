
float3 send_ray(t_ray *ray, t_scene *scene) {

	float t;
	int hit_id;
	float3 backColor = 0;
	float intensity;
	float3 resColor = 0;

	if (!is_intersect(ray, scene->objects, scene->num_obj, &hit_id, &t))
		return backColor;
	t_object hit_obj = scene->objects[hit_id];
	ray->t = t;
	ray->hitPoint = ray->origin + t * ray->dir;
	ray->hitNormal = get_normal(&hit_obj, ray);
	ray->hit_id = hit_id;
	intensity = get_light_intensity(ray, scene);
	resColor = get_obj_color(&hit_obj, ray, scene) * intensity;
	return resColor;
}


void init_ray(t_ray *ray, CAMERA *cam, int work_id, float rand)
{

	ray->origin = cam->origin;
	float x = work_id % cam->screen_w;
	float y = work_id / cam->screen_w;
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
}
