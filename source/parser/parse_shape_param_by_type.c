#include "parser.h"

static void	parse_shape_param_0_1(const JC_FIELD shape_field, cl_float *param,
								const char *child_name)
{
	*param = jc_get_float(shape_field, child_name);
	if (*param < 0.1f)
		parse_error(jc_full_name(shape_field), child_name,
				"The value must be greater or equal than 0.1");
}

static void	parse_shape_angle(const JC_FIELD shape_field, cl_float *angle)
{
	*angle = jc_get_float(shape_field, "angle");
	if (*angle < 1.0f || *angle > 89.0f)
		parse_error(jc_full_name(shape_field), "angle",
					"Value must be in range [1.0; 89.0].");
	*angle = deg_to_rad(*angle);
}

static void	parse_triangle_dots(const JC_FIELD shape_field, FLT3 *dots)
{
	JC_FIELD	dots_field;

	dots_field = jc_get_field(shape_field, "dots", JC_OBJ);
	dots[0] = parse_cl_float3(dots_field, "a");
	dots[1] = parse_cl_float3(dots_field, "b");
	dots[2] = parse_cl_float3(dots_field, "c");
}

void		parse_shape_param_by_type(const JC_FIELD shape_field,
									SHAPE_TYPE type, FLT3 *params)
{

	params[0] = (FLT3){0.0f, 0.0f, 0.0f};
	params[1] = (FLT3){1.0f, 1.0f, 0.0f};
	params[2] = (FLT3){0.0f, 0.0f, 1.0f};
	if (type == PLANE)
		(void)type;
	else if (type == SPHERE || type == CYLINDER || type == CIRCLE)
		parse_shape_param_0_1(shape_field, &params[0].x, "radius");
	else if (type == CONE)
		parse_shape_angle(shape_field, &params[0].x);
	else if (type == CAPPEDCYLINDER || type == CAPPEDPLANE)
	{
		parse_shape_param_0_1(shape_field, &params[0].x,
			(type == CAPPEDPLANE) ? "width" : "radius");
		parse_shape_param_0_1(shape_field, &params[0].y, "height");
	}
	else if (type == TRIANGLE)
		parse_triangle_dots(shape_field, params);
	else
		ft_error("Unknown action (parse_shape_param_by_type)");
}
