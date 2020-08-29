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

FLT3		parse_shape_param_by_type(const JC_FIELD shape_field,
													SHAPE_TYPE type)
{
	FLT3	params;

	params = (FLT3){0.0f, 0.0f, 0.0f};
	if (type == PLANE)
		(void)type;
	else if (type == SPHERE || type == CYLINDER || type == CIRCLE)
		parse_shape_param_0_1(shape_field, &params.x, "radius");
	else if (type == CONE)
		parse_shape_angle(shape_field, &params.x);
	else if (type == CAPPEDCYLINDER || type == CAPPEDPLANE)
	{
		parse_shape_param_0_1(shape_field, &params.x,
			(type == CAPPEDPLANE) ? "width" : "radius");
		parse_shape_param_0_1(shape_field, &params.y, "height");
	}
	else if (type == TRIANGLE)
		params = parse_cl_float3_or_default(shape_field, "origin", params);
	else
		ft_error("Unknown action (parse_shape_param_by_type)");
	return (params);
}
