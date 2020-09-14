/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serialize_shapes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:32:25 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:32:25 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serializer.h"

static void	s_name_float_value_comma(t_serializer *s, const char *name,
									cl_float value)
{
	s_name(s, name);
	s_float(s, value);
	s_comma(s);
}

static void	s_shape_params_with_comma(t_serializer *s, SHAPE_TYPE type,
									FLT3 *params)
{
	if (type == PLANE || type == TRIANGLE || type == OFF)
		(void)type;
	else if (type == SPHERE || type == CYLINDER || type == CIRCLE)
		s_name_float_value_comma(s, "radius", params->x);
	else if (type == CONE)
		s_name_float_value_comma(s, "angle", rad_to_deg(params->x));
	else if (type == CAPPEDCONE)
	{
		s_name_float_value_comma(s, "angle", rad_to_deg(params->x));
		s_name_float_value_comma(s, "height", params->y);
		s_name_float_value_comma(s, "shift", params->z);
	}
	else if (type == CAPPEDCYLINDER || type == CAPPEDPLANE || type == BOX ||
			type == CAPSULE)
	{
		s_name_float_value_comma(s,
			(type == CAPPEDCYLINDER || type == CAPSULE) ? "radius" : "width",
			params->x);
		s_name_float_value_comma(s, "height", params->y);
		if (type == BOX)
			s_name_float_value_comma(s, "depth", params->z);
	}
	else
		ft_error("Unknown action (s_shape_params_with_comma)");
}

static void	s_shape_obj(t_serializer *s, SHAPE *shape, SCENE *scene)
{
	s_open_obj(s);
	s_name(s, "type");
	s_str_in_quotes_free(s, get_shape_type_name(shape->dto->type));
	s_comma(s);
	s_name(s, "name");
	s_str_in_quotes(s, shape->name);
	s_comma(s);
	if (shape->dto->type == OFF)
	{
		s_name(s, "path");
		s_str_in_quotes(s,
			ft_strstr(scene->off.filename, OFF_PATH) + ft_strlen(OFF_PATH));
		s_comma(s);
	}
	s_shape_params_with_comma(s, shape->dto->type, &shape->dto->params);
	s_transform_obj(s, &shape->dto->transform, shape->dto->type);
	s_comma(s);
	s_material_obj(s, &shape->dto->material);
	s_comma(s);
	s_shape_texture_obj(s, shape->dto->texture.id, scene->textures);
	s_comma(s);
	s_shape_normal_map_obj(s, shape->dto->normal_map.id, scene->normal_maps);
	s_comma(s);
	s_sections_obj(s, shape->dto);
	s_close_obj(s);
}

void		s_shapes_arr(t_serializer *s, SHAPE *shape, SCENE *scene)
{
	s_open_arr_with_name(s, "shapes");
	while (shape)
	{
		s_shape_obj(s, shape, scene);
		if (shape->next)
			s_comma(s);
		shape = shape->next;
	}
	s_close_arr(s);
}
