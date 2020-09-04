

float		semi_sphere_intersect(t_ray *ray, t_object *sphere, float3 cut_normal)
{
	float3		new_origin;
	float		coef[3];
	float		discriminant;
	float2		t;

	new_origin = ray->origin - sphere->transform.position;
	coef[0] = dot(ray->dir, ray->dir);
	coef[1] = 2.0 * dot(ray->dir, new_origin);
	coef[2] = dot(new_origin, new_origin) - sphere->params.x * sphere->params.x;
	discriminant = coef[1] * coef[1] - 4.0 * coef[0] * coef[2];
	if (discriminant < 0.0f)
		return (-1.0f);

	t.x = (-coef[1] - sqrt(discriminant)) / (2.0 * coef[0]);
	t.y = (-coef[1] + sqrt(discriminant)) / (2.0 * coef[0]);

	float3	t_point[2];

	t_point[0] = ray->origin + t.x * ray->dir;
	t_point[1] = ray->origin + t.y * ray->dir;

	t = cut_by_plane_section(t_point, sphere->transform.position, cut_normal, t);

	float min_t = minT(t.x, t.y);
	if (sphere->working_sections && min_t > MY_EPSILON && min_t < ray->t)
		return compute_sections(ray, sphere->section, sphere->is_complex_section, t.x, t.y);
	return min_t;
}

float		semi_cylinder_intersect(t_ray *ray, t_object *cylinder, float len)
{
	float		abcd[4];
	float2		t;
	float3		x;

	x = ray->origin - cylinder->transform.position;
	abcd[0] = dot(ray->dir, ray->dir) - pow(dot(ray->dir, cylinder->transform.direction), 2);
	abcd[1] = 2 * (dot(ray->dir, x) - (dot(ray->dir, cylinder->transform.direction) * dot(x, cylinder->transform.direction)));
	abcd[2] = dot(x, x) - pow(dot(x, cylinder->transform.direction), 2) - cylinder->params.x * cylinder->params.x;
	abcd[3] = pow(abcd[1], 2) - 4 * abcd[0] * abcd[2];
	if (abcd[3] < 0)
		return 0;
	t.x = (-abcd[1] + sqrt(abcd[3])) / (2 * abcd[0]);
	t.y = (-abcd[1] - sqrt(abcd[3])) / (2 * abcd[0]);

	float3	t_point[2];

	t_point[0] = ray->origin + t.x * ray->dir;
	t_point[1] = ray->origin + t.y * ray->dir;

	t = cut_by_plane_section(t_point, cylinder->transform.position + cylinder->transform.direction * len / 2, cylinder->transform.direction, t);
	t = cut_by_plane_section(t_point, cylinder->transform.position - cylinder->transform.direction * len / 2, -cylinder->transform.direction, t);

	float min_t = minT(t.x, t.y);
	if (cylinder->working_sections && min_t > MY_EPSILON && min_t < ray->t)
		return compute_sections(ray, cylinder->section, cylinder->is_complex_section, t.x, t.y);
	return min_t;
}


float	semi_cone_intersect(t_ray *ray, t_object *cone, float len, float shift)
{
	float		abc[3];
	float2		t;
	float3		x;
	float		k_and_discr[2];

	x = ray->origin - (cone->transform.position + shift * cone->transform.direction);
	k_and_discr[0] = 1 + tan(cone->params.x) * tan(cone->params.x);
	abc[0] = dot(ray->dir, ray->dir) - k_and_discr[0] * pow(dot(ray->dir, cone->transform.direction), 2);
	abc[1] = 2 * (dot(ray->dir, x) - k_and_discr[0] * dot(ray->dir, cone->transform.direction) * dot(x, cone->transform.direction));
	abc[2] = dot(x,x) - k_and_discr[0] * pow(dot(x, cone->transform.direction), 2);
	k_and_discr[1] = pow(abc[1], 2) - 4 * abc[0] * abc[2];
	if (k_and_discr[1] < 0)
		return (0);
	t.x = (-abc[1] + sqrt(k_and_discr[1])) / (2 * abc[0]);
	t.y = (-abc[1] - sqrt(k_and_discr[1])) / (2 * abc[0]);

	float3	t_point[2];

	t_point[0] = ray->origin + t.x * ray->dir;
	t_point[1] = ray->origin + t.y * ray->dir;

	t = cut_by_plane_section(t_point, cone->transform.position + cone->transform.direction * len / 2, cone->transform.direction, t);
	t = cut_by_plane_section(t_point, cone->transform.position - cone->transform.direction * len / 2, -cone->transform.direction, t);

	float min_t = minT(t.x, t.y);
	if (cone->working_sections && min_t > MY_EPSILON && min_t < ray->t)
		return compute_sections(ray, cone->section, cone->is_complex_section, t.x, t.y);
	return min_t;
}

