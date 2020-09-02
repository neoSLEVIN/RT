#include "serializer.h"

static void	s_name_float_value_comma(t_serializer *s, const char *name,
									cl_float value)
{
	s_name(s, name);
	s_float(s, value);
	s_comma(s);
}

static void	s_triangle_dots_with_comma(t_serializer *s, FLT3 *dots)
{
	s_open_obj_with_name(s, "dots");
	s_name(s, "a");
	s_float3(s, dots[0]);
	s_comma(s);
	s_name(s, "b");
	s_float3(s, dots[1]);
	s_comma(s);
	s_name(s, "c");
	s_float3(s, dots[2]);
	s_close_obj(s);
	s_comma(s);
}

static void	s_shape_params_with_comma(t_serializer *s, SHAPE_TYPE type,
									FLT3 *params)
{
	if (type == PLANE)
		(void)type;
	else if (type == SPHERE || type == CYLINDER || type == CIRCLE)
		s_name_float_value_comma(s, "radius", params[0].x);
	else if (type == CONE)
		s_name_float_value_comma(s, "angle", rad_to_deg(params[0].x));
	else if (type == CAPPEDCYLINDER || type == CAPPEDPLANE)
	{
		s_name_float_value_comma(s, (type == CAPPEDPLANE) ? "width" : "radius",
								params[0].x);
		s_name_float_value_comma(s, "height", params[0].y);
	}
	else if (type == TRIANGLE)
		s_triangle_dots_with_comma(s, params);
	else
		ft_error("Unknown action (s_shape_params_with_comma)");
}

static void	s_shape_obj(t_serializer *s, SHAPE *shape,
					PPM_IMG *textures, PPM_IMG *normal_maps)
{
	s_open_obj(s);
	s_name(s, "type");
	s_str_in_quotes_free(s, get_shape_type_name(shape->dto->type));
	s_comma(s);
	s_name(s, "name");
	s_str_in_quotes(s, shape->name);
	s_comma(s);
	s_shape_params_with_comma(s, shape->dto->type, shape->dto->params);
	s_transform_obj(s, &shape->dto->transform, shape->dto->type);
	s_comma(s);
	s_material_obj(s, &shape->dto->material);
	s_comma(s);
	s_shape_texture_obj(s, shape->dto->texture.id, textures);
	s_comma(s);
	s_shape_normal_map_obj(s, shape->dto->normal_map.id, normal_maps);
	s_comma(s);
	s_sections_obj(s, shape->dto);
	s_close_obj(s);
}

void		s_shapes_arr(t_serializer *s, SHAPE *shape,
					PPM_IMG *textures, PPM_IMG *normal_maps)
{
	s_open_arr_with_name(s, "shapes");
	while (shape)
	{
		s_shape_obj(s, shape, textures, normal_maps);
		if (shape->next)
			s_comma(s);
		shape = shape->next;
	}
	s_close_arr(s);
}
