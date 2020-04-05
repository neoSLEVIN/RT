/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_transform_by_obj.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/05 06:05:13 by cschoen           #+#    #+#             */
/*   Updated: 2020/04/05 06:05:13 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_transform	get_transform_by_obj(const json_object *obj,
										const char *parent_name)
{
	t_transform	transform;
	char		*child_name;

	if (json_object_get_type(obj) != json_type_object)
	{
		ft_printf("Error:\tThe value type must be an object: %s",
				parent_name);
		exit(1);
	}
	child_name = parent_dot_child(parent_name, "position");
	transform.position =
		get_vec3_by_obj(get_obj_by_key("position", obj), child_name);
	ft_strdel(&child_name);
	child_name = parent_dot_child(parent_name, "rotation");
	transform.rotation =
		get_vec3_by_obj(get_obj_by_key("rotation", obj), child_name);
	ft_strdel(&child_name);
	return (transform);
}
