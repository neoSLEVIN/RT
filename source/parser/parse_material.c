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

static _Bool	from_zero_till_one(float value)
{
	if (value >= 0 && value <= 1)
		return (TRUE);
	return (FALSE);
}

static void		validate_material(MATERIAL material, JC_FIELD material_field)
{
	if (!(from_zero_till_one(material.specular)))
	{
		parse_error(jc_full_name(material_field), "specular",
			"Value must be in range [0.0; 1.0].");
	}
	if (!(from_zero_till_one(material.reflective)))
	{
		parse_error(jc_full_name(material_field), "reflective",
			"Value must be in range [0.0; 1.0].");
	}
	if (!(from_zero_till_one(material.transparency)))
	{
		parse_error(jc_full_name(material_field), "transparency",
			"Value must be in range [0.0; 1.0].");
	}
	if (!(from_zero_till_one(material.refraction)))
	{
		parse_error(jc_full_name(material_field), "refraction",
			"Value must be in range [0.0; 1.0].");
	}
}

MATERIAL		parse_material(const JC_FIELD parent, const char *child_name)
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
		material.refraction = 0.0f;
		return (material);
	}
	material.color = parse_color_or_default(material_field, "color", "f");
	material.specular =
		jc_get_float_or_default(material_field, "specular", 0.0f);
	material.reflective =
		jc_get_float_or_default(material_field, "reflective", 0.0f);
	material.transparency =
		jc_get_float_or_default(material_field, "transparency", 0.0f);
	material.refraction =
		jc_get_float_or_default(material_field, "refraction", 0.0f);
	validate_material(material, material_field);
	return (material);
}
