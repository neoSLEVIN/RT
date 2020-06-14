/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_shape.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/27 03:28:29 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char		*unnamed_shape(size_t index)
{
	char	*name;
	char	*str_index;

	if (!(str_index = ft_itoa((int)index)))
		ft_error("Can't allocate memory");
	if (!(name = ft_strnew(ft_strlen("Unnamed_") + ft_strlen(str_index))))
		ft_error("Can't allocate memory");
	ft_strcpy(name, "Unnamed_");
	ft_strcat(name, str_index);
	ft_strdel(&str_index);
	return (name);
}

static float	parse_shape_param_by_type(const JC_FIELD shape_field,
										SHAPE_TYPE type)
{
	float	param;

	if (type == PLANE)
		param = 0.0f;
	else if (type == SPHERE || type == CYLINDER || type == CAPPEDCYLINDER
	|| type == ELLIPSOID || type == ELLIPSE)
	{
		param = jc_get_float(shape_field, "radius");
		if (param < 0.1f)
			parse_error(jc_full_name(shape_field), "radius",
				"The value must be greater or equal than 0.1");
	}
	else if (type == CONE)
	{
		param = jc_get_float(shape_field, "angle");
		if (param < 1.0f || param > 89.0f)
			parse_error(jc_full_name(shape_field), "angle",
				"Value must be in range [1.0; 89.0].");
		param = deg_to_rad(param);
	}
	else
		ft_error("Unknown action");
	return (param);
}

static void		init_default_shape_params(SHAPE *shape)
{
	shape->prev = NULL;
	shape->next = NULL;
	shape->widgets = NULL;
	shape->tree_iter = NULL;
	shape->dto->marker = FALSE;
	shape->texture_name = NULL;
	shape->normal_map_name = NULL;
}

SHAPE			*parse_shape_idx(const JC_FIELD parent, const size_t index,
								PPM_IMG *textures, PPM_IMG *normal_maps)
{
	JC_FIELD	shape_field;
	SHAPE		*shape;
	size_t		length;

	shape_field = jc_get_field_idx(parent, index, JC_OBJ);
	shape = (SHAPE*)malloc(sizeof(SHAPE));
	if (!shape || !(shape->dto = (DTO_SHAPE*)malloc(sizeof(DTO_SHAPE))))
		ft_error("Can't allocate memory");
	init_default_shape_params(shape);
	shape->name = jc_get_string(shape_field, "name", TRUE);
	if (!shape->name)
		shape->name = unnamed_shape(index);
	length = ft_strlen(shape->name);
	if (length == 0 || length > 20)
		parse_error(jc_full_name(shape_field), "name",
			"The field length must be in the range (0; 20].");
	shape->dto->type = parse_shape_type(shape_field, "type");
	shape->dto->param =
		parse_shape_param_by_type(shape_field, shape->dto->type);
	shape->dto->transform = parse_transform(shape_field, "transform");
	shape->dto->material = parse_material(shape_field, "material");
	shape->dto->texture = parse_texture_info_in_shape(shape_field, "texture",
		&shape->texture_name, textures);
	shape->dto->normal_map = parse_texture_info_in_shape(shape_field,
		"normal map", &shape->normal_map_name, normal_maps);
	parse_sections(shape_field, "sections", shape->dto);
	return (shape);
}

SHAPE			*parse_shapes(const JC_FIELD parent, const char *child_name,
							PPM_IMG *textures, PPM_IMG *normal_maps)
{
	JC_FIELD	shapes_field;
	SHAPE		*shapes;
	SHAPE		*temp_shape;
	size_t		length;
	size_t		i;

	shapes_field = jc_get_field(parent, child_name, (JC_ARR | JC_NULL));
	if (jc_is_null(shapes_field))
		return (NULL);
	length = jc_get_array_length(shapes_field);
	if (length == 0)
		return (NULL);
	shapes = parse_shape_idx(shapes_field, 0, textures, normal_maps);
	temp_shape = shapes;
	i = 0;
	while (++i < length)
	{
		temp_shape->next = parse_shape_idx(shapes_field, i, textures, normal_maps);
		temp_shape->next->prev = temp_shape;
		temp_shape = temp_shape->next;
	}
	return (shapes);
}
