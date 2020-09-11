

float triangle_intersect(t_ray *ray, t_object *triangle)
{
	float3 normal;
	float3 x;
	float3 v[3];
	float t;
	float d;
	float3 c[3];

	/*вычисляем стороны AB BC CA*/
	v[0] = triangle->transform.dots[1] - triangle->transform.dots[0];
	v[1] = triangle->transform.dots[2] - triangle->transform.dots[1];
	v[2] = triangle->transform.dots[0] - triangle->transform.dots[2];
	x = ray->origin - triangle->transform.dots[0];
	normal = normalize(cross(v[0], v[1]));//нормаль для проверки перпендикулярности луча и нормали
	if ((d = dot(ray->dir, normal)) == 0.0f)
		return (-1.0f);
	//находим точку пересечения
	t = -dot(x, normal) / d;
	float3 hitPoint = ray->origin + t * ray->dir;
	//находим вектора от каждой точки треугольника до точки пересечения AP BP CP
	c[0] = hitPoint - triangle->transform.dots[0];
	c[1] = hitPoint - triangle->transform.dots[1];
	c[2] = hitPoint - triangle->transform.dots[2];
	//проверяем что площади получившихся параллелограммов AB AP + BC BP + CA CP < AB BC + eps
	//eps нужна для того, если точка лежит на границе треугольника
	if (length(cross(v[0], c[0])) + length(cross(v[1], c[1])) + length(cross(v[2], c[2])) < length(cross(v[1], v[2])) + 0.001f)
	{
		if (triangle->working_sections && t > MY_EPSILON && t < ray->t)
			return compute_sections(ray, triangle->section, triangle->is_complex_section, -1.0f, t);
		return (t);
	}
	return (-1.0f);
}

float off_intersect(t_ray *ray, t_object *off, t_scene *scene, int *part_index)
{
	int i = -1;
	float t = -1.0f;
	t_object obj = *off;

	while (++i < scene->faces_cnt)
	{
		obj.transform.dots[0] = scene->points[scene->faces[i].x] + obj.transform.position;
		obj.transform.dots[1] = scene->points[scene->faces[i].y] + obj.transform.position;
		obj.transform.dots[2] = scene->points[scene->faces[i].z] + obj.transform.position;
		t = minTwithIndexes(t, triangle_intersect(ray, &obj), *part_index, i, part_index);
	}
	return t;
}

void make_ray_empty(t_ray *ray) {
	ray->t = MY_INFINITY;
	ray->hitPoint = 0.0f;
	ray->hitNormal = 0.0f;
	ray->hit_id = -1;
	ray->hit_type = NONE;
	ray->index = -1;
}


void set_t(t_ray *ray, t_object *selected_obj, t_transparent_obj *skiped, float t, int i, int part_index) {
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
			ray->index = part_index;
		}
	}
}

void	reinit_off_obj(t_object *obj, t_scene *scene, t_ray *ray)
{
	int index = ray->index;
	if (index >= scene->point_cnt)
		index = 0;
	obj->transform.dots[0] = scene->points[scene->faces[index].x] + obj->transform.position;
	obj->transform.dots[1] = scene->points[scene->faces[index].y] + obj->transform.position;
	obj->transform.dots[2] = scene->points[scene->faces[index].z] + obj->transform.position;

	obj->transform.position =
		(obj->transform.dots[0] + obj->transform.dots[1] + obj->transform.dots[2]) / 3;

	if (scene->colors[index].x >= 0)
		obj->material.color = scene->colors[index];
}

/*skiped можно поставить в 0, если требуется пересечения со всеми объектами*/
bool is_intersect(t_ray *ray, t_scene *scene, t_transparent_obj *skiped)
{

	int i = 0;
	int part_index;
	float t = 0;
	make_ray_empty(ray);

	while (i < scene->num_obj)
	{
		part_index = -1;
		t_object selected_obj = scene->objects[i];
		if (selected_obj.type == SPHERE)
			t = sphere_intersect(ray, &selected_obj);
		else if (selected_obj.type == PLANE)
			t = plane_intersect(ray, &selected_obj);
		else if (selected_obj.type == CYLINDER)
			t = cylinder_intersect(ray, &selected_obj);
		else if (selected_obj.type == CAPSULE)
			t = capsule_intersect(ray, &selected_obj, &part_index);
		else if (selected_obj.type == CONE)
			t = cone_intersect(ray, &selected_obj);
		else if (selected_obj.type == CAPPEDCONE)
			t = capped_cone_intersect(ray, &selected_obj, &part_index);
		else if (selected_obj.type == CAPPEDCYLINDER)
			t = capped_cylinder_intersect(ray, &selected_obj);
		else if (selected_obj.type == CIRCLE)
			t = circle_intersect(ray, &selected_obj);
		else if (selected_obj.type == CAPPEDPLANE)
			t = cappedplane_intersect(ray, &selected_obj);
		else if (selected_obj.type == BOX)
			t = box_intersect(ray, &selected_obj, &part_index);
		else if (selected_obj.type == TRIANGLE)
			t = triangle_intersect(ray, &selected_obj);
		else if (selected_obj.type == OFF)
			t = off_intersect(ray, &selected_obj, scene, &part_index);
		if (t > MY_EPSILON && t < ray->t) {
			set_t(ray, &selected_obj, skiped, t, i, part_index);
		}
		i++;
	}
	bool intersected = ray->t < MY_INFINITY;
	if (intersected) {
		t_object hit_obj = scene->objects[ray->hit_id];
		if (hit_obj.type == OFF)
		{
			reinit_off_obj(&hit_obj, scene, ray);
		}
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

float module(float a)
{
	return a < 0 ? -a : a;
}

