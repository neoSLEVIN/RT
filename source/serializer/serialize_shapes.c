#include "serializer.h"

static void	s_shape_params_with_comma(t_serializer *s, SHAPE_TYPE type,
									FLT3 *params)
{
	if (type == PLANE)
		(void)type;
	else if (type == SPHERE || type == CYLINDER)
	{
		s_name(s, "radius");
		s_float(s, params->x);
		s_comma(s);
	}
	else if (type == CONE)
	{
		s_name(s, "angle");
		s_float(s, deg_to_rad(params->x));
		s_comma(s);
	}
	else if (type == CAPPEDCYLINDER)
	{
		s_name(s, "radius");
		s_float(s, params->x);
		s_comma(s);
		s_name(s, "height");
		s_float(s, params->y);
		s_comma(s);
	}
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
	s_shape_params_with_comma(s, shape->dto->type, &shape->dto->params);
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
