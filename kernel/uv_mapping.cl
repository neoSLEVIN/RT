
/*Везде преобразуем 3d координаты в 2d - uv [0,1]*/

float2 sphere_map(t_object *obj, t_ray *ray) {
	float2 uv;
	
	float x = ray->hitPoint.x - obj->transform.position.x;
	float y = ray->hitPoint.y - obj->transform.position.y;
	float z = ray->hitPoint.z - obj->transform.position.z;
	
	/*azimut from -pi to pi */
	float theta = atan2(z, x);
	/*polar angle 0 to pi*/
	float phi = acos(y / (obj->params.x));
	/* from 0 to 1 */
	float raw_u = 0.5f + theta / (2 * M_PI);
	
	uv.x = raw_u;
	uv.y = phi / M_PI;
	return uv;
}

float2 translate_plane_coord_with_static(float3 plane_norm, t_ray *ray, float3 plane_pos) {
	float3 u_basis;
	float3 v_basis;
	float2 coord;

	set_uv_basis(plane_norm, &u_basis, &v_basis);
	coord.x = dot(u_basis, ray->hitPoint - plane_pos);
	coord.y = dot(v_basis, ray->hitPoint - plane_pos);
	return coord;
}

float2 plane_map(t_object *obj, t_ray *ray, int size) {
	float2 uv;
	float2 coord;
	if (obj->type == TRIANGLE || obj->type == OFF) {
		coord = translate_plane_coord_with_static(triangle_normal(obj), ray, obj->transform.position);
	} else {
		coord = translate_plane_coord_with_static(obj->transform.direction, ray, obj->transform.position);
	}

	/*Плодадь ничем не ограничена, поэтому все разделено на области со сторонами size*/
	uv.x = fmod(coord.x, size) / (float)(size);
	uv.y = fmod(coord.y, size) / (float)(size);
	/*если брать модуль то будет зеркально. Когда текстура шахматы, в 0 типа двойная клетка*/
	if (uv.x < 0)
		uv.x = 1 + uv.x;
	if (uv.y < 0)
		uv.y = 1 + uv.y;
	return uv;
}

float2 box_map(t_object *obj, t_ray *ray, int size) {
	t_object plane = *obj;

	if (ray->index < 2) {
		plane.transform.position += (ray->index == 1 ? 1 : -1) *
									plane.transform.direction * plane.params.z / 2;
	} else if (ray->index < 4) {
		plane.transform.direction =
			normalize(cross(plane.transform.direction, plane.transform.rotation));

		plane.transform.position += (ray->index == 3 ? 1 : -1) *
									plane.transform.direction * plane.params.y / 2;
		plane.params.y = plane.params.z;
	} else {
		float3 forward = plane.transform.direction;
		plane.transform.direction = plane.transform.rotation;
		plane.transform.rotation = forward;

		plane.transform.position += (ray->index == 5 ? 1 : -1) *
									plane.transform.direction * plane.params.x / 2;
		plane.params.x = plane.params.z;
	}
	return plane_map(&plane, ray, size);
}

/*Подходит и для конуса*/
float2 cylindrical_map(t_object *obj, t_ray *ray, int size) {
	float2 uv;
	
	float3 u_basis;
	float3 v_basis;
	
	float3 normal = obj->transform.direction;
	set_uv_basis(obj->transform.direction, &u_basis, &v_basis);
	 
	float3 vec = ray->hitPoint - obj->transform.position;
	float x = dot(vec, u_basis);
	float y = dot(vec, normal);
	float z = dot(vec, v_basis);
	
	/*azimut angle -0.5 to 0.5*/
	float phi = atan2(z, x) / (2 * M_PI);
	uv.x = phi + 0.5f;
	uv.y = fmod(y, size) / (float)(size);
	if (uv.y < 0)
		uv.y = 1 + uv.y;
	return uv;
}

float2 capped_cone_map(t_object *obj, t_ray *ray, int size) {
	if (ray->index == 0)
		return cylindrical_map(obj, ray, size);

	t_object plane = *obj;

	if (ray->index == 1) {
		plane.transform.position += plane.transform.direction * plane.params.y / 2;
	} else {
		plane.transform.position -= plane.transform.direction * plane.params.y / 2;
		plane.transform.direction = -plane.transform.direction;
	}
	return plane_map(&plane, ray, size);
}

float2 capped_cylindrical_map(t_object *obj, t_ray *ray, int size) {
	t_object plane = *obj;

	/*Скалярное произведение вектора (из двух точек на крышке и в центре крышки) и dir равно 0. Однако с флотами есть погрешность*/
	float3 centerTop = obj->transform.position + obj->transform.direction * (obj->params.y / 2.0f);
	float3 centerBottom = obj->transform.position - obj->transform.direction * (obj->params.y / 2.0f);
	if (fabs(dot(centerTop - ray->hitPoint, obj->transform.direction)) < 0.01f) {
		plane.transform.position += plane.transform.direction * plane.params.y / 2;
		return plane_map(&plane, ray, size);
	} else if (fabs(dot(centerBottom - ray->hitPoint, obj->transform.direction)) < 0.01f) {
		plane.transform.position -= plane.transform.direction * plane.params.y / 2;
		plane.transform.direction = -plane.transform.direction;
		return plane_map(&plane, ray, size);
	}
	return cylindrical_map(obj, ray, size);
}

float2 translate_plane_coord(float3 plane_norm, t_ray *ray) {
	float3 u_basis;
	float3 v_basis;
	float2 coord;
	
	set_uv_basis(plane_norm, &u_basis, &v_basis);
	coord.x = dot(u_basis, ray->hitPoint);
	coord.y = dot(v_basis, ray->hitPoint);
	return coord;
}

/*Нужно чтобы uv координаты не отличались при повороте фигуры*/
void set_uv_basis(float3 normal, float3 *u_basis, float3 *v_basis) {

	if (normal.x != 0 && normal.y != 0) {
		float3 tmp;
		tmp.s0 = normal.y;
		tmp.s1 = -normal.x;
		tmp.s2 = 0.f;
		*u_basis = normalize(tmp);
	} else if (normal.x == 0){
		*u_basis = (float3)(1, 0, 0);
	} else if (normal.y == 0) {
		*u_basis = (float3)(0, 1, 0);
	} else {
		*u_basis = (float3)(0, 0, 1);
	}
	*v_basis =  cross(normal, *u_basis);
}
