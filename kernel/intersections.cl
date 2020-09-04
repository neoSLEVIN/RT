

/*Intersection*/

float minTwithIndexes(float a, float b, int index_a, int index_b, int *result_index) {
	if (a > 0 && b > 0) {
		*result_index = (a < b) ? index_a : index_b;
		return a < b ? a : b;
	}
	if (a > 0 && b < 0) {
		*result_index = index_a;
		return a;
	}
	*result_index = index_b;
	return b;
}

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
		return (-1.0f);

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

float capsule_intersect(t_ray *ray, t_object *capsule, int *index)
{
	t_object	obj = *capsule;
	float		t[3];

	t[0] = semi_cylinder_intersect(ray, &obj, obj.params.y);

	obj.transform.position += obj.transform.direction * obj.params.y / 2;
	t[1] = semi_sphere_intersect(ray, &obj, -obj.transform.direction);

	obj.transform.position -= obj.transform.direction * obj.params.y;
	t[2] = semi_sphere_intersect(ray, &obj, obj.transform.direction);

	float res_t = t[0];
	res_t = minTwithIndexes(res_t, t[1], 0, 1, index);
	res_t = minTwithIndexes(res_t, t[2], *index, 2, index);
	return res_t;
}

float capped_cone_intersect(t_ray *ray, t_object *capped_cone, int *index)
{
	t_object	obj = *capped_cone;
	float		t[3];

	t[0] = semi_cone_intersect(ray, &obj, obj.params.y, obj.params.z);

	obj.transform.position += obj.transform.direction * obj.params.y / 2;
	obj.params.x = fabs(obj.params.z - obj.params.y / 2) * tan(capped_cone->params.x);
	t[1] = circle_intersect(ray, &obj);

	obj.transform.position -= obj.transform.direction * obj.params.y;
	obj.params.x = fabs(obj.params.z + obj.params.y / 2) * tan(capped_cone->params.x);
	obj.transform.direction = -obj.transform.direction;
	t[2] = circle_intersect(ray, &obj);

	float res_t = t[0];
	res_t = minTwithIndexes(res_t, t[1], 0, 1, index);
	res_t = minTwithIndexes(res_t, t[2], *index, 2, index);
	return res_t;
}

/*У нас два базиса UV, на них проецируем hitpoint и сравниваем с длинной и шириной*/
float cappedplane_intersect(t_ray *ray, t_object *plane)
{
    float    t;
    float3   hitPoint;
    float3   u;
    float3   v;
    
    t = plane_intersect(ray, plane);
	if (fabs(t) < 0.1f) {
		return -1.0f;
	}
    hitPoint = ray->origin + t * ray->dir;
	
	u = plane->transform.rotation;
	v = cross(plane->transform.direction, u);

    float3 w_vec = plane->params.x * u;
	float3 h_vec = plane->params.y * v;
	float3 fromOrigToHit = plane->transform.position + w_vec / 2 + h_vec / 2 - hitPoint;

    float w_projection = dot(fromOrigToHit, w_vec) / plane->params.x;
    float h_projection = dot(fromOrigToHit, h_vec) / plane->params.y;
    if (w_projection < 0 || w_projection > plane->params.x) {
        return -1.0f;
    } else if (h_projection < 0 || h_projection > plane->params.y) {
        return -1.0f;
    }
    return t;
}

float box_intersect(t_ray *ray, t_object *cube, int *index)
{
	float	t[6];
	t_object plane = *cube;

	float3 resolution = plane.params;
	float3 center = plane.transform.position;
	float3 forward = plane.transform.direction;
	float3 left = plane.transform.rotation;
	float3 up = normalize(cross(forward, left));

	// FRONT
	plane.transform.position = center + forward * resolution.z / 2;
	t[0] = cappedplane_intersect(ray, &plane);
	// BACK
	plane.transform.position = center - forward * resolution.z / 2;
	t[1] = cappedplane_intersect(ray, &plane);

	plane.transform.direction = up;
	plane.params.y = resolution.z;

	// UP
	plane.transform.position = center + up * resolution.y / 2;
	t[2] = cappedplane_intersect(ray, &plane);
	// BOTTOM
	plane.transform.position = center - up * resolution.y / 2;
	t[3] = cappedplane_intersect(ray, &plane);

	plane.transform.direction = left;
	plane.transform.rotation = forward;
	plane.params.x = resolution.z;
	plane.params.y = resolution.y;

	// LEFT
	plane.transform.position = center + left * resolution.x / 2;
	t[4] = cappedplane_intersect(ray, &plane);
	// RIGHT
	plane.transform.position = center - left * resolution.x / 2;
	t[5] = cappedplane_intersect(ray, &plane);

	float res_t = t[0];
	res_t = minTwithIndexes(res_t, t[1], 0, 1, index);
	res_t = minTwithIndexes(res_t, t[2], *index, 2, index);
	res_t = minTwithIndexes(res_t, t[3], *index, 3, index);
	res_t = minTwithIndexes(res_t, t[4], *index, 4, index);
	res_t = minTwithIndexes(res_t, t[5], *index, 5, index);

	return res_t;
}

