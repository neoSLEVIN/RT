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


float		add_section_on_primitive(t_ray *ray, t_object *object, float t1, float t2, int section)
{
	t_object	section_plane;

	if (section == 0)
		section_plane.transform.direction = object->section.x.direction;
	else if (section == 1)
		section_plane.transform.direction = object->section.y.direction;
	else if (section == 2)
		section_plane.transform.direction = object->section.z.direction;
	section_plane.transform.position = object->section.x.position;

	float3 norm_vector = section_plane.transform.direction;

	float3 t1_point = ray->origin + t1 * ray->dir;
	float3 t2_point = ray->origin + t2 * ray->dir;
	float3 section_to_t1 = t1_point - section_plane.transform.position;
	float3 section_to_t2 = t2_point - section_plane.transform.position;

	if (length(section_to_t1) == 0.0f) {
		t1 = -1.0f;
	}
	if (length(section_to_t2) == 0.0f) {
		t2 = -1.0f;
	}
	float cos_a = dot(section_to_t1, norm_vector) / (length(section_to_t1) * length(norm_vector));
	if (cos_a >= 0)
		t1 = -1.0f;
	cos_a = dot(section_to_t2, norm_vector) / (length(section_to_t2) * length(norm_vector));
	if (cos_a >= 0)
		t2 = -1.0f;
	return minT(t1, t2);
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

	if (sphere->section.on_x || sphere->section.on_y || sphere->section.on_z)
	{
		float3		section;
		section.x = MY_INFINITY;
		section.y = MY_INFINITY;
		section.z = MY_INFINITY;
		if (sphere->section.on_x)
			section.x = add_section_on_primitive(ray, sphere, t[0], t[1], 0);
		if (sphere->section.on_y)
			section.y = add_section_on_primitive(ray, sphere, t[0], t[1], 1);
		if (sphere->section.on_z)
			section.z = add_section_on_primitive(ray, sphere, t[0], t[1], 2);
		return minT(minT(section.x, section.y), section.z);
	}
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


	if (cylinder->section.on_x || cylinder->section.on_y || cylinder->section.on_z)
	{
		float3		section;
		section.x = MY_INFINITY;
		section.y = MY_INFINITY;
		section.z = MY_INFINITY;
		if (cylinder->section.on_x)
			section.x = add_section_on_primitive(ray, cylinder, t[0], t[1], 0);
		if (cylinder->section.on_y)
			section.y = add_section_on_primitive(ray, cylinder, t[0], t[1], 1);
		if (cylinder->section.on_z)
			section.z = add_section_on_primitive(ray, cylinder, t[0], t[1], 2);
		return minT(minT(section.x, section.y), section.z);
	}
	
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

	if (cone->section.on_x || cone->section.on_y || cone->section.on_z)
	{
		float3		section;
		section.x = MY_INFINITY;
		section.y = MY_INFINITY;
		section.z = MY_INFINITY;
		if (cone->section.on_x)
			section.x = add_section_on_primitive(ray, cone, t[0], t[1], 0);
		if (cone->section.on_y)
			section.y = add_section_on_primitive(ray, cone, t[0], t[1], 1);
		if (cone->section.on_z)
			section.z = add_section_on_primitive(ray, cone, t[0], t[1], 2);
		return minT(minT(section.x, section.y), section.z);
	}
	return minT(t[0], t[1]);
}

float capped_cylinder_intersect(t_ray *ray, t_object *capped_cylinder)
{
	float3 abc[2];
	float tmp[7];
	float t;
	float y;
	float3 rarb[2];

	rarb[0] = capped_cylinder->transform.position - capped_cylinder->transform.direction * capped_cylinder->radius;
	rarb[1] = capped_cylinder->transform.position + capped_cylinder->transform.direction * capped_cylinder->radius;
	abc[0] = rarb[1] - rarb[0];/*ca*/
	abc[1] = ray->origin - rarb[0]; /*oc*/
	tmp[0] = dot(abc[0], abc[0]); 	/*caca*/
	tmp[1] = dot(abc[0], ray->dir); /*card*/
	tmp[2] = dot(abc[0], abc[1]);	/*caoc*/
	tmp[3] = tmp[0] - pow(tmp[1], 2); /*a*/
	tmp[4] = tmp[0] * dot(abc[1], ray->dir) - tmp[2] * tmp[1]; /*b*/
	tmp[5] = tmp[0] * dot(abc[1], abc[1]) - pow(tmp[2], 2) - pow(capped_cylinder->radius, 2) * tmp[0];/*c*/
	tmp[6] = pow(tmp[4], 2) - tmp[3] * tmp[5]; /*h*/
	if (tmp[6] < 0)
		return (0);
	tmp[6] = sqrt(tmp[6]);
	t = (-tmp[4] - tmp[6]) / tmp[3];
	y = tmp[2] + t * tmp[1];
	if (y > 0.0f && y < tmp[0])
		return t;
	t = (((y < 0.0) ? 0.0 : tmp[0]) - tmp[2]) / tmp[1];
	if ((module(tmp[4] + tmp[3] * t)) < tmp[6])
		return t;
	return (0);
}


void make_ray_empty(t_ray *ray) {
	ray->t = MY_INFINITY;
	ray->hitPoint = 0.0f;
	ray->hitNormal = 0.0f;
	ray->hit_id = -1;
	ray->hit_type = NONE;
}


void set_t(t_ray *ray, t_object *selected_obj, t_transparent_obj *skiped, float t, int i) {
	/*Пропускаем прозрачные объекты, если нам передали не null*/
	if (skiped != 0 && selected_obj->material.transparency > 0) {
		/*ищем ближайший прозрачный объект*/
		if (skiped->t > t) {
			skiped->t = t;
			skiped->hit_id = i;
		}
	/*пересекли обычный объект*/
	} else {
		ray->t = t;
		ray->hit_id = i;
	}
}

/*skiped можно поставить в 0, если требуется пересечения со всеми объектами*/
bool is_intersect(t_ray *ray, t_scene *scene, t_transparent_obj *skiped)
{

	int i = 0;
	float t = 0;
	make_ray_empty(ray);

	while (i < scene->num_obj)
	{
		t_object selected_obj = scene->objects[i];
		if (selected_obj.type == SPHERE)
			t = sphere_intersect(ray, &selected_obj);
		else if (selected_obj.type == PLANE)
			t = plane_intersect(ray, &selected_obj);
		else if (selected_obj.type == CYLINDER)
			t = cylinder_intersect(ray, &selected_obj);
		else if (selected_obj.type == CONE)
			t = cone_intersect(ray, &selected_obj);
		else if (selected_obj.type == CAPPEDCYLINDER)
        	t = capped_cylinder_intersect(ray, &selected_obj);
		if (t > MY_EPSILON && t < ray->t) {
			set_t(ray, &selected_obj, skiped, t, i);
		}
		i++;
	}
	bool intersected = ray->t < MY_INFINITY;
	if (intersected) {
		t_object hit_obj = scene->objects[ray->hit_id];
		ray->hitPoint = ray->origin + ray->t * ray->dir;
		ray->hitNormal = get_normal(&hit_obj, ray);
		ray->hit_type = hit_obj.type;
	}
	return intersected;
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

float module(float a)
{
	return a < 0 ? -a : a;
}
