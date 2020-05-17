
float3 get_obj_color(t_object *obj, t_ray *ray) {
	float3 color;
	if (!obj->marker)
		return (float3)(0.8f, 0.8f, 0.8f);
	if (obj->type == PLANE) {
		float sines = sin(ray->hitPoint.x) * sin(ray->hitPoint.y) * sin(ray->hitPoint.z);
		if (sines < 0) {
			color = obj->material.color;
		} else {
			color = 1.0f;
		}
	} else {
		color = obj->material.color;
	}
	return color;
}

char convertColorFromFloat(float f) {
	return floor(f >= 1.0 ? 255 : f * 256.0);
}
