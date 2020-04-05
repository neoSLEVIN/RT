/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_vec3_by_obj.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/05 06:03:41 by cschoen           #+#    #+#             */
/*   Updated: 2020/04/05 06:03:41 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_vec3	get_vec3_by_obj(const json_object *obj, const char *parent_name)
{
	t_vec3	v3;
	char	*child_name;

	if (json_object_get_type(obj) != json_type_object)
	{
		ft_printf("Error:\tThe value type must be an object: %s",
				parent_name);
		exit(1);
	}
	child_name = parent_dot_child(parent_name, "x");
	v3.x = get_float_by_obj(get_obj_by_key("x", obj), child_name);
	ft_strdel(&child_name);
	child_name = parent_dot_child(parent_name, "y");
	v3.y = get_float_by_obj(get_obj_by_key("y", obj), child_name);
	ft_strdel(&child_name);
	child_name = parent_dot_child(parent_name, "z");
	v3.z = get_float_by_obj(get_obj_by_key("z", obj), child_name);
	ft_strdel(&child_name);
	return (v3);
}
