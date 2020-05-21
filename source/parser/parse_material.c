/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_material.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/21 04:50:17 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	validate_color_texture(const char *texture_name,
									const JC_FIELD material)
{
	char	*err;

	err = "Must contain at least one of the following fields: |color|texture|";
	if (jc_is_null(jc_get_field(material, "color", (JC_STR | JC_NULL))) &&
			texture_name == NULL)
		parse_error(jc_full_name(material), NULL, err);
}

MATERIAL	parse_material(const JC_FIELD parent, const char *child_name,
							char **texture_name, TEXTURE *textures)
{
	JC_FIELD	material_field;
	MATERIAL	material;

	material_field = jc_get_field(parent, child_name, JC_OBJ);
	if (!(*texture_name = jc_get_string(material_field, "texture", TRUE)))
		material.texture_id = -1;
	else if ((material.texture_id = check_for_texture_name(textures,
												*texture_name)) == -1)
		parse_error(jc_full_name(material_field), "name",
					"There is no field with this name");
	material.color = parse_color_or_default(material_field, "color", "f");
	validate_color_texture(*texture_name, material_field);
	material.specular = jc_get_float(material_field, "specular");
	// TODO jc_get_int(material_field, "specular");
	material.reflective = jc_get_float(material_field, "reflective");
	material.transparency =
		jc_get_float(material_field, "transparency");
	// TODO add validation for params
	return (material);
}
