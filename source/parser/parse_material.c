/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_material.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/05 06:07:36 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/06 02:40:18 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

MATERIAL	parse_material(const JC_FIELD parent, const char *child_name)
{
	JC_FIELD	material_field;
	MATERIAL	material;

	material_field = jc_get_field(child_name, parent, JC_OBJ);
	material.color = parse_color(material_field, "color");
	material.specular = jc_get_float(material_field, "specular");
	// TODO jc_get_int(material_field, "specular");
	material.reflective = jc_get_float(material_field, "reflective");
	material.transparency =
		jc_get_float(material_field, "transparency");
	// TODO add validation for params
	return (material);
}
