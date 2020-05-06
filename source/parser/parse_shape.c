/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_shape.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 00:29:45 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/06 05:58:45 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

float	degrees_to_rad(float angle_in_degrees)
{
	return ((angle_in_degrees * PI / 180.0) / 2);
}

static float	parse_shape_param_by_type(const JC_FIELD shape_field,
										SHAPE_TYPE type)
{
	float	param;

	if (type == PLANE)
		param = 0.0f;
	else if (type == SPHERE || type == CYLINDER)
	{
		param = jc_get_float(shape_field, "radius");
		if (param <= 0.0f)
			parse_error(jc_full_name(shape_field), "radius",
				" Value must be positive.");
	}
	else if (type == CONE)
	{
		param = jc_get_float(shape_field, "angle");
		if (param <= 0.0f || param >= 180.0f)
			parse_error(jc_full_name(shape_field), "angle",
				" Value must be in range (0.0; 180.0).");
		param = degrees_to_rad(param);
	}
	else
		ft_error("Unknown action");
	return (param);
}

SHAPE			*parse_shape_idx(const JC_FIELD parent, const int index)
{
	JC_FIELD	shape_field;
	SHAPE		*shape;

	shape_field = jc_get_field_idx(index, parent, JC_OBJ);
	if((shape = (SHAPE*)malloc(sizeof(SHAPE))) == NULL)
		ft_error("Can't allocate memory");
	shape->next = NULL;
	shape->dto.uid = index;
	shape->dto.marker = FALSE;
	shape->dto.transform = parse_transform(shape_field, "transform");
	shape->dto.material = parse_material(shape_field, "material");
	shape->dto.type = parse_shape_type(shape_field, "type");
	shape->dto.param = parse_shape_param_by_type(shape_field, shape->dto.type);
	return (shape);
}

SHAPE			*parse_shapes(const JC_FIELD parent, const char *child_name)
{
	JC_FIELD	shapes_field;
	SHAPE		*shapes;
	SHAPE		*temp_shape;
	size_t		length;
	size_t		i;

	shapes_field = jc_get_field(child_name, parent, (JC_ARR | JC_NULL));
	if (jc_is_null(shapes_field))
		return (NULL);
	length = jc_get_array_length(shapes_field);
	if (length == 0)
		return (NULL);
	shapes = parse_shape_idx(shapes_field, 0);
	temp_shape = shapes;
	i = 0;
	while (++i < length)
	{
		temp_shape->next = parse_shape_idx(shapes_field, i);
		temp_shape = temp_shape->next;
	}
	return (shapes);
}
