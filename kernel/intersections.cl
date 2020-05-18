/*Nazarov*/
void		init_section_plane(t_object *object)
{
	object->section.on_x = false;
	object->section.on_y = false;
	object->section.on_z = false;
	object->section.x.position = object->transform.position;
	object->section.y.position = object->transform.position;
	object->section.z.position = object->transform.position;
	object->section.x.direction.x = 1;
	object->section.x.direction.y = 0;
	object->section.x.direction.z = 0;
	object->section.y.direction.x = 0;
	object->section.y.direction.y = 1;
	object->section.y.direction.z = 0;
	object->section.z.direction.x = 0;
	object->section.z.direction.y = 0;
	object->section.z.direction.z = 1;
	object->section.color = object->material.color;
}


/*Nazarov*/
float		add_section_on_primitive(t_ray *ray, t_object *object, float t1, float t2)
{
	t_object	section_plane;

	if (object->section.on_x)
		section_plane.transform.direction = object->section.x.direction;
	else if (object->section.on_y)
		section_plane.transform.direction = object->section.y.direction;
	else if (object->section.on_z)
		section_plane.transform.direction = object->section.z.direction;
	section_plane.transform.position = object->section.x.position;

	/*1. Растояние на луче до секущей площади*/
	float origin_ray_to_section_plane = plane_intersect(ray, &section_plane);

	/*2. Растояние до точек входа и выхода из объекта на луче*/
	float ray_exit_point = t1 > t2 ? t1 : t2;
	float ray_entry_point = t1 < t2 ? t1 : t2;

	float3 intersect_point = ray->origin + origin_ray_to_section_plane * ray->dir;
	float3 entry_point = ray->origin + ray_entry_point * ray->dir;
	
	if (ray_entry_point == origin_ray_to_section_plane)
	{
		return ray_entry_point;
	}

	/*Расчитываем растояние от точки входа в объект до центра секущей плоскости, с помощью нового луча ray_to_center_section_plane (rtcsp)*/
	t_ray rtcsp;
	rtcsp.origin = entry_point;

	rtcsp.dir.x = section_plane.transform.position.x - rtcsp.origin.x;
	rtcsp.dir.y = section_plane.transform.position.y - rtcsp.origin.y;
	rtcsp.dir.z = section_plane.transform.position.z - rtcsp.origin.z;

	rtcsp.t = plane_intersect(&rtcsp, &section_plane);

	/*Ищем cos между нормалью секущей плоскости (norm_vector) и вектором из центра этой плоскости к точке входа в объект (temp_vector)*/
	float3 temp_vector;
	temp_vector.x = rtcsp.origin.x - section_plane.transform.position.x;
	temp_vector.y = rtcsp.origin.y - section_plane.transform.position.y;
	temp_vector.z = rtcsp.origin.z - section_plane.transform.position.z;

	float3 norm_vector = section_plane.transform.direction;
	float3 tv = temp_vector;
	float3 nv = norm_vector;

	float cos_a = (nv.x * tv.x + nv.y * tv.y + nv.z * tv.z)/(sqrt(nv.x * nv.x + nv.y * nv.y + nv.z * nv.z) * sqrt(tv.x * tv.x + tv.y * tv.y + tv.z * tv.z));

	/*Зная cos угла (cos_a) и растояние до центра плоскости (rtcsp.t), находим длину перпендикуляра к плоскости от точки пересечения исходного луча с секущей плоскостью (intersect_point)*/
	float d = rtcsp.t * cos_a;

	/*Если растояние > 0 то данная часть объекта отсечена плоскостью и не отображается, соответственно луч должен продолжить движение до следующего объекта на сцене*/
	if (origin_ray_to_section_plane > ray_entry_point && origin_ray_to_section_plane < ray_exit_point)
		return plane_intersect(ray, &section_plane);
	if (d < 0)
		return (0);

	return ray_entry_point;
}

/********************************************************************/


/*Intersection*/

float		sphere_intersect(t_ray *ray, t_object *sphere)
{
	float3		new_origin;
	float		coef[3];
	float		discriminant;
	float		t[2];

	new_origin = ray->origin - sphere->transform.position;
	coef[0] = dot(ray->dir, ray->dir);
	coef[1] = 2.0 * dot(ray->dir, new_origin);
	coef[2] = dot(new_origin, new_origin) - sphere->radius * sphere->radius;
	discriminant = coef[1] * coef[1] - 4.0 * coef[0] * coef[2];
	if (discriminant < 0.0 ){
		return (0);
	}
	t[0] = (-coef[1] - sqrt(discriminant)) / (2.0 * coef[0]);
	t[1] = (-coef[1] + sqrt(discriminant)) / (2.0 * coef[0]);

	/*Сечение - Nazarov*/
	init_section_plane(sphere);
	sphere->section.on_x = false;
	if (sphere->section.on_x || sphere->section.on_y || sphere->section.on_z)
		return add_section_on_primitive(ray, sphere, t[0], t[1]);
	return minT(t[0], t[1]);
}

float	plane_intersect(t_ray *ray, t_object *plane)
{
	float3	temp;
	float	d_dot_n;
	float	t;

	if ((d_dot_n = dot(ray->dir, plane->transform.direction)) == 0.0)
		return 0;
	temp = plane->transform.position - ray->origin;
	t = dot(temp, plane->transform.direction) / d_dot_n;
	return t;
}

float		cylinder_intersect(t_ray *ray, t_object *cylinder)
{
	float		abcd[4];
	float		t[2];
	float3		x;

	x = ray->origin - cylinder->transform.position;
	abcd[0] = dot(ray->dir, ray->dir) - pow(dot(ray->dir, cylinder->transform.direction), 2);
	abcd[1] = 2 * (dot(ray->dir, x) - (dot(ray->dir, cylinder->transform.direction) * dot(x, cylinder->transform.direction)));
	abcd[2] = dot(x, x) - pow(dot(x, cylinder->transform.direction), 2) - cylinder->radius * cylinder->radius;
	abcd[3] = pow(abcd[1], 2) - 4 * abcd[0] * abcd[2];
	if (abcd[3] < 0)
		return 0;
	t[0] = (-abcd[1] + sqrt(abcd[3])) / (2 * abcd[0]);
	t[1] = (-abcd[1] - sqrt(abcd[3])) / (2 * abcd[0]);
	
	/*Сечение - Nazarov*/
	init_section_plane(cylinder);
	cylinder->section.on_z = false;
	if (cylinder->section.on_x || cylinder->section.on_y || cylinder->section.on_z)
		return add_section_on_primitive(ray, cylinder, t[0], t[1]);
	
	return minT(t[0], t[1]);
}

float	cone_intersect(t_ray *ray, t_object *cone)
{
	float		abc[3];
	float		t[2];
	float3		x;
	float		k_and_discr[2];

	x = ray->origin - cone->transform.position;
	k_and_discr[0] = 1 + tan(cone->radius) * tan(cone->radius);
	abc[0] = dot(ray->dir, ray->dir) - k_and_discr[0] * pow(dot(ray->dir, cone->transform.direction), 2);
	abc[1] = 2 * (dot(ray->dir, x) - k_and_discr[0] * dot(ray->dir, cone->transform.direction) * dot(x, cone->transform.direction));
	abc[2] = dot(x,x) - k_and_discr[0] * pow(dot(x, cone->transform.direction), 2);
	k_and_discr[1] = pow(abc[1], 2) - 4 * abc[0] * abc[2];
	if (k_and_discr[1] < 0)
		return (0);
	t[0] = (-abc[1] + sqrt(k_and_discr[1])) / (2 * abc[0]);
	t[1] = (-abc[1] - sqrt(k_and_discr[1])) / (2 * abc[0]);
	
	/*Сечение - Nazarov*/
	init_section_plane(cone);
	cone->section.on_x = false;
	if (cone->section.on_x || cone->section.on_y || cone->section.on_z)
		return add_section_on_primitive(ray, cone, t[0], t[1]);
	return minT(t[0], t[1]);
}


bool is_intersect(t_ray *ray, __global t_object *obj, int num_obj, int* hit_id, float* distance)
{
	float inf = 1e20f;
	*distance = inf;

	int i = 0;
	float t = 0;
	/*TODO просмотреть другие места где сбрасывается hit_id*/
	ray->hit_id = -1;
	*hit_id = -1;
	while (i < num_obj)
	{
		t_object a1 = obj[i];
		if (obj[i].type == SPHERE)
			t = sphere_intersect(ray, &a1);
		else if (obj[i].type == PLANE)
			t = plane_intersect(ray, &a1);
		else if (obj[i].type == CYLINDER)
			t = cylinder_intersect(ray, &a1);
		else if (obj[i].type == CONE)
			t = cone_intersect(ray, &a1);
		if (t > EPSILON && t < *distance) {
			*distance = t;
			*hit_id = i;
		}
		i++;
	}
	return *distance < inf;
}

float minT(float a, float b) {
	if (a > 0 && b > 0) {
		return a < b ? a : b;
	}
	if (a > 0 && b < 0) {
		return a;
	}
	return b;
}
