/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jc_get_material.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/05 06:07:36 by cschoen           #+#    #+#             */
/*   Updated: 2020/04/06 01:15:56 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_material	jc_get_material(const t_field *parent, const char *child_name)
{
	t_field		material_field;
	t_material	material;

	material_field = jc_get_field(child_name, parent, json_type_object);
	material.color = jc_get_color(&material_field, "color");
	material.specular = jc_get_float(&material_field, "specular");
	jc_clear_field(&material_field);
	return (material);
}
