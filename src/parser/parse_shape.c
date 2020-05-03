/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_shape.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 00:29:45 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/04 01:46:39 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	*parse_shape_fields_by_type(const JC_FIELD parent, SHAPE_TYPE type)
{
	if (type == PLANE)
		return (parse_plane(parent));
	else if (type == SPHERE)
		return (parse_sphere(parent));
	else if (type == CONE)
		return (parse_cone(parent));
	else if (type == CYLINDER)
		return (parse_cylinder(parent));
	else
		ft_error("Unknown action");
	return (NULL);
}

SHAPE_LIST	*parse_shape_idx(const JC_FIELD parent, const int index)
{
	JC_FIELD	shape_field;
	SHAPE_LIST	*shape;

	shape_field = jc_get_field_idx(index, parent, JC_OBJ);
	if(!(shape = (SHAPE_LIST*)malloc(sizeof(SHAPE_LIST))))
		ft_error("Can't allocate memory");
	shape->uid = g_uid++;
	shape->marker = FALSE;
	shape->next = NULL;
	shape->type = parse_shape_type(shape_field, "type");
	shape->shape = parse_shape_fields_by_type(shape_field, shape->type);
	return (shape);
}

SHAPE_LIST	*parse_shapes(const JC_FIELD parent, const char *child_name)
{
	JC_FIELD	shapes_field;
	SHAPE_LIST	*shapes;
	SHAPE_LIST	*temp_shape;
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
