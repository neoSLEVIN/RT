
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
	if (discriminant < 0.0) {
		return (0);
	}
	t[0] = (-coef[1] - sqrt(discriminant)) / (2.0 * coef[0]);
	t[1] = (-coef[1] + sqrt(discriminant)) / (2.0 * coef[0]);
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
