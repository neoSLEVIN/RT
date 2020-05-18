
/*Везде преобразуем 3d координаты в 2d - uv [0,1]*/

float2 sphere_map(t_object *obj, t_ray *ray) {
	float2 uv;
	
	float x = ray->hitPoint.x - obj->transform.position.x;
	float y = ray->hitPoint.y - obj->transform.position.y;
	float z = ray->hitPoint.z - obj->transform.position.z;
	
	/*azimut from -pi to pi */
	float theta = atan2(z, x);
	/*polar angle 0 to pi*/
	float phi = acos(y / (obj->radius));
	/* from 0 to 1 */
	float raw_u = 0.5f + theta / (2 * M_PI);
	
	uv.x = raw_u;
	uv.y = phi / M_PI;
	return uv;
}

float2 plane_map(t_object *obj, t_ray *ray, int size) {
	float2 uv;
	float2 coord = translate_plane_coord(ray);
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

float2 translate_plane_coord(t_ray *ray) {
	float3 u_basis;
	float3 v_basis;
	float2 coord;
	
	set_uv_basis(ray->hitNormal, &u_basis, &v_basis);
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
	} else {
		*u_basis = (float3)(1, 0, 0);
	}
	*v_basis =  cross(normal, *u_basis);
}
