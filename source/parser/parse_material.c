/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_material.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/23 13:24:08 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

MATERIAL	parse_material(const JC_FIELD parent, const char *child_name)
{
	JC_FIELD	material_field;
	MATERIAL	material;

	material_field = jc_get_field(parent, child_name, (JC_OBJ | JC_NULL));
	if (jc_is_null(material_field))
	{
		material.color = (FLT3){1.0f, 1.0f, 1.0f};
		material.specular = 0;
		material.reflective = 0.0f;
		material.transparency = 0.0f;
		return (material);
	}
	material.color = parse_color_or_default(material_field, "color", "f");
	material.specular =
		jc_get_float_or_default(material_field, "specular", 0.0f);
	// TODO jc_get_int(material_field, "specular");
	material.reflective =
		jc_get_float_or_default(material_field, "reflective", 0.0f);
	material.transparency =
		jc_get_float_or_default(material_field, "transparency", 0.0f);
	// TODO add validation for params
	return (material);
}
