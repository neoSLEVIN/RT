/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jc_get_shapes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/05 16:39:38 by cschoen           #+#    #+#             */
/*   Updated: 2020/04/06 04:25:32 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_list_shape	*jc_get_shapes(const t_field *parent, const char *child_name)
{
	t_field			shapes_field;
	t_list_shape	*shapes;
	t_list_shape	*first_shape;
	size_t			length;
	size_t			i;

	first_shape = NULL;
	shapes_field = jc_get_nullable_field(child_name, parent, json_type_array);
	length = jc_get_array_length(&shapes_field);
	i = -1;
	while (++i < length)
	{
		if (i == 0)
		{
			first_shape = jc_get_shape(&shapes_field, i);
			shapes = first_shape;
		}
		else
		{
			shapes->next = jc_get_shape(&shapes_field, i);
			shapes = shapes->next;
		}
	}
	jc_clear_field(&shapes_field);
	return (first_shape);
}
