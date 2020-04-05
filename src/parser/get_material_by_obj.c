/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_material_by_obj.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/05 06:07:36 by cschoen           #+#    #+#             */
/*   Updated: 2020/04/05 06:07:36 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_material	get_material_by_obj(const json_object *obj, const char *parent_name)
{
	t_material	material;
	char		*child_name;

	if (json_object_get_type(obj) != json_type_object)
	{
		ft_printf("Error:\tThe value type must be an object: %s",
				parent_name);
		exit(1);
	}
	child_name = parent_dot_child(parent_name, "color");
	material.color =
		get_color_by_obj(get_obj_by_key("color", obj), child_name);
	ft_strdel(&child_name);
	child_name = parent_dot_child(parent_name, "specular");
	material.specular =
		get_float_by_obj(get_obj_by_key("specular", obj), child_name);
	ft_strdel(&child_name);
	return (material);
}
