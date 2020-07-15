/*Procedure textures*/

float3 uv_patter_checker(int checkerW, int checkerH, float2 uv) {
	float3 color;
	
	int u2 = floor(uv.x * checkerW);
	int v2 = floor(uv.y * checkerH);
	
	if ((u2 + v2) % 2 == 0) {
		color = 1.0f;
		return color;
	} else {
		color = 0.0f;
		return color;
	}
}

float3 uv_patter_lines(float2 uv) {
	float3 color;
	if (uv.y > 0.95 || uv.y < 0.05)
		color = 1.0f;
	else
		color = 0.0f;
	return color;
}

float3 uv_patter_plane_lines_cross(float2 uv) {
	float3 color;
	if (uv.x > 0.95 || uv.x < 0.05 || uv.y > 0.95 || uv.y < 0.05)
		color = 1.0f;
	else
		color = 0.0f;
	return color;
}

float3 uv_patter_circle(float2 uv, t_object *obj) {
	float len = length((uv - (float2)(0.5f)) * 3.14f * 30);
	return (obj->material.color * (cos(len)));
}

/*Основан на глобальных координатах. Меньше шума*/
float3 plane_checker(t_object *obj, t_ray *ray) {
	float3 color = 1.0f;
	float2 coord = translate_plane_coord(obj->transform.direction, ray);
	float sines = sin(coord.x) * sin(coord.y);
	if (sines < 0) {
		return obj->material.color;
	}
	return color;
}

float3 plane_lines_cross(t_object *obj, t_ray *ray) {
	float3 color = 1.0f;
	float2 coord = translate_plane_coord(obj->transform.direction, ray);
	float sines1 = sin(coord.x * 2);
	float sines2 = sin(coord.y * 2);
	if ((sines1 < 0.99) && (sines2 < 0.98)) {
		return obj->material.color;
	}
	return color;
}
