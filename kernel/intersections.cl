

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
	coef[2] = dot(new_origin, new_origin) - sphere->params.x * sphere->params.x;
	discriminant = coef[1] * coef[1] - 4.0 * coef[0] * coef[2];
	if (discriminant < 0.0f)
		return (0);

	t[0] = (-coef[1] - sqrt(discriminant)) / (2.0 * coef[0]);
	t[1] = (-coef[1] + sqrt(discriminant)) / (2.0 * coef[0]);

	float min_t = minT(t[0], t[1]);
	if (sphere->working_sections && min_t > MY_EPSILON && min_t < ray->t)
		return compute_sections(ray, sphere->section, sphere->is_complex_section, t[0], t[1]);
	return min_t;
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

	if (plane->working_sections && t > MY_EPSILON && t < ray->t)
		return compute_sections(ray, plane->section, plane->is_complex_section, -1.0f, t);
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
	abcd[2] = dot(x, x) - pow(dot(x, cylinder->transform.direction), 2) - cylinder->params.x * cylinder->params.x;
	abcd[3] = pow(abcd[1], 2) - 4 * abcd[0] * abcd[2];
	if (abcd[3] < 0)
		return 0;
	t[0] = (-abcd[1] + sqrt(abcd[3])) / (2 * abcd[0]);
	t[1] = (-abcd[1] - sqrt(abcd[3])) / (2 * abcd[0]);

	float min_t = minT(t[0], t[1]);
	if (cylinder->working_sections && min_t > MY_EPSILON && min_t < ray->t)
		return compute_sections(ray, cylinder->section, cylinder->is_complex_section, t[0], t[1]);
	return min_t;
}

float	cone_intersect(t_ray *ray, t_object *cone)
{
	float		abc[3];
	float		t[2];
	float3		x;
	float		k_and_discr[2];

	x = ray->origin - cone->transform.position;
	k_and_discr[0] = 1 + tan(cone->params.x) * tan(cone->params.x);
	abc[0] = dot(ray->dir, ray->dir) - k_and_discr[0] * pow(dot(ray->dir, cone->transform.direction), 2);
	abc[1] = 2 * (dot(ray->dir, x) - k_and_discr[0] * dot(ray->dir, cone->transform.direction) * dot(x, cone->transform.direction));
	abc[2] = dot(x,x) - k_and_discr[0] * pow(dot(x, cone->transform.direction), 2);
	k_and_discr[1] = pow(abc[1], 2) - 4 * abc[0] * abc[2];
	if (k_and_discr[1] < 0)
		return (0);
	t[0] = (-abc[1] + sqrt(k_and_discr[1])) / (2 * abc[0]);
	t[1] = (-abc[1] - sqrt(k_and_discr[1])) / (2 * abc[0]);

	float min_t = minT(t[0], t[1]);
	if (cone->working_sections && min_t > MY_EPSILON && min_t < ray->t)
		return compute_sections(ray, cone->section, cone->is_complex_section, t[0], t[1]);
	return min_t;
}

float capped_cylinder_intersect(t_ray *ray, t_object *capped_cylinder)
{
	float		abcd[4];
	float		t[4] = {-1.0f, -1.0f, -1.0f, -1.0f};
	float3		x;
	float		d_dot_n;

	x = ray->origin - capped_cylinder->transform.position;
	abcd[0] = dot(ray->dir, ray->dir) - pow(dot(ray->dir, capped_cylinder->transform.direction), 2);
	abcd[1] = 2 * (dot(ray->dir, x) - (dot(ray->dir, capped_cylinder->transform.direction) * dot(x, capped_cylinder->transform.direction)));
	abcd[2] = dot(x, x) - pow(dot(x, capped_cylinder->transform.direction), 2) - capped_cylinder->params.x * capped_cylinder->params.x;
	abcd[3] = pow(abcd[1], 2) - 4 * abcd[0] * abcd[2];
	if (abcd[3] >= 0) {
		t[0] = (-abcd[1] + sqrt(abcd[3])) / (2 * abcd[0]);
		t[1] = (-abcd[1] - sqrt(abcd[3])) / (2 * abcd[0]);
		if (is_outside_capped_cylinder(ray, capped_cylinder, t[0]))
			t[0] = -1.0f;
		if (is_outside_capped_cylinder(ray, capped_cylinder, t[1]))
			t[1] = -1.0f;
	}

	x = capped_cylinder->transform.position + capped_cylinder->transform.direction * capped_cylinder->params.y / 2.0f - ray->origin;
	if ((d_dot_n = dot(ray->dir, capped_cylinder->transform.direction)) != 0.0f) {
		t[2] = dot(x, capped_cylinder->transform.direction) / d_dot_n;
		if (is_outside_capped_cylinder(ray, capped_cylinder, t[2]))
			t[2] = -1.0f;
	}

	x = capped_cylinder->transform.position - capped_cylinder->transform.direction * capped_cylinder->params.y / 2.0f - ray->origin;
	if ((d_dot_n = dot(ray->dir, -capped_cylinder->transform.direction)) != 0.0f) {
		t[3] = dot(x, -capped_cylinder->transform.direction) / d_dot_n;
		if (is_outside_capped_cylinder(ray, capped_cylinder, t[3]))
			t[3] = -1.0f;
	}

	float min_t;
	if (minT(t[0], t[1]) <= 0.0f)
		min_t = minT(t[2], t[3]);
	else
		min_t = minT(minT(t[0], t[1]), minT(t[2], t[3]));
	if (capped_cylinder->working_sections && min_t > MY_EPSILON && min_t < ray->t)
	{
		if (minT(t[0], t[1]) <= 0.0f) {
			return compute_sections(ray, capped_cylinder->section, capped_cylinder->is_complex_section, t[2], t[3]);
		} else if (minT(t[2], t[3]) <= 0.0f) {
			return compute_sections(ray, capped_cylinder->section, capped_cylinder->is_complex_section, t[0], t[1]);
		} else {
			return compute_sections(ray, capped_cylinder->section, capped_cylinder->is_complex_section, minT(t[0], t[1]), minT(t[2], t[3]));
		}
	}
	return min_t;
}


float	circle_intersect(t_ray *ray, t_object *circle)
{
	float	t;
	float3 hitPoint;
	
	t = plane_intersect(ray, circle);
	hitPoint = ray->origin + t * ray->dir;
	if (length(circle->transform.position - hitPoint) > circle->params.x) {
		return -1.0f;
	}
	return t;
}

/*странно крутится*/
float cappedplane_instersect1(t_ray *ray, t_object *plane)
{
	float	t;
	float2 	coord;

	t = plane_intersect(ray, plane);
	ray->hitPoint = ray->origin + t * ray->dir;
	coord = translate_plane_coord(plane->transform.direction, ray);
	float left = plane->transform.position.x - plane->params.x / 2.0f;
	float right = plane->transform.position.x +  plane->params.x / 2.0f;
	float up = plane->transform.position.y + plane->params.y / 2.0f;
	float down = plane->transform.position.y - plane->params.y / 2.0f;
	if (coord.x <= left || coord.x >= right)
		return -1.0f;
	if (coord.y <= down || coord.y >= up)
		return -1.0f;
	return t;
}

float cappedplane_instersect2(t_ray *ray, t_object *plane)
{
    float    t;
    float3   hitPoint;
    float3   u;
    float3   v;
    
    t = plane_intersect(ray, plane);
    hitPoint = ray->origin + t * ray->dir;
    set_uv_basis(plane->transform.direction, &u, &v);
    
    float3 fromOrigToHit = plane->transform.position - hitPoint;
    float3 w_vec = plane->params.x * u;
    float3 h_vec = plane->params.y * v;
    
    float w_projection = dot(fromOrigToHit, w_vec) / plane->params.x;
    float h_projection = dot(fromOrigToHit, h_vec) / plane->params.y;
    if (w_projection < 0 || w_projection > plane->params.x) {
        return -1.0f;
    } else if (h_projection < 0 || h_projection > plane->params.y) {
        return -1.0f;
    }
    return t;
}


float cappedplane_instersect(t_ray *ray, t_object *plane)
{
    float    t;
    float    t1;

    
    t = cappedplane_instersect2(ray, plane);
    plane->transform.position = plane->transform.position + plane->transform.direction * 3;
    t1 = cappedplane_instersect2(ray, plane);
    return minT(t, t1);
}


/*Из-за нормализации direction коряво рисуется*/
float triangle_intersect(t_ray *ray, t_object *triangle)
{
	float3 normal;
	float3 x;
	float3 v[3];
	float t;
	float d;
	float3 c[3];

	/*вычисляем стороны AB BC CA*/
	v[0] = triangle->transform.direction - triangle->transform.position;
	v[1] = triangle->transform.rotation - triangle->transform.direction;
	v[2] = triangle->transform.position - triangle->transform.rotation;
	x = ray->origin - triangle->transform.position;
	normal = normalize(cross(v[0], v[1]));//нормаль для проверки перпендикулярности луча и нормали
	if ((d = dot(ray->dir, normal)) == 0.0f)
		return (-1.0f);
	//находим точку пересечения
	t = -dot(x, normal) / d;
	ray->hitPoint = ray->origin + t * ray->dir;
	//находим вектора от каждой точки треугольника до точки пересечения AP BP CP
	c[0] = ray->hitPoint - triangle->transform.position;
	c[1] = ray->hitPoint - triangle->transform.direction;
	c[2] = ray->hitPoint - triangle->transform.rotation;
	//проверяем что площади получившихся параллелограммов AB AP + BC BP + CA CP < AB BC + eps
	//eps нужна для того, если точка лежит на границе треугольника
	if (length(cross(v[0], c[0])) + length(cross(v[1], c[1])) + length(cross(v[2], c[2])) < length(cross(v[1], v[2])) + MY_EPSILON)
		return (t);
	return (-1.0f);
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
		/*Отдаем приоритет непрозрачным объектам*/
		if (!(selected_obj->material.transparency > 0 && fabs(t - ray->t) < 1))
		{
			ray->t = t;
			ray->hit_id = i;
		}
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
		else if (selected_obj.type == CIRCLE)
			t = circle_intersect(ray, &selected_obj);
		else if (selected_obj.type == CAPPEDPLANE)
			t = cappedplane_instersect(ray, &selected_obj);
		else if (selected_obj.type == TRIANGLE)
			t = triangle_intersect(ray, &selected_obj);
		if (t > MY_EPSILON && t < ray->t) {
			set_t(ray, &selected_obj, skiped, t, i);
		}
		i++;
	}
	bool intersected = ray->t < MY_INFINITY;
	if (intersected) {
		t_object hit_obj = scene->objects[ray->hit_id];
		ray->hitPoint = ray->origin + ray->t * ray->dir;
		ray->hit_type = hit_obj.type;
		ray->hitNormal = get_normal(&hit_obj, ray, scene);
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

float nothingOrMaxT(float a, float b) {
	if (a < 0 || b < 0) {
		return a < b ? a : b;
	}
	return a > b ? a : b;
}

float module(float a)
{
	return a < 0 ? -a : a;
}
