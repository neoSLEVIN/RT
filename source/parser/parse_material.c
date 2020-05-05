/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_material.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/05 06:07:36 by cschoen           #+#    #+#             */
//*   Updated: 2020/05/05 07:37:29 by cschoen          ###   ########lyon.fr   *//*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_material	parse_material(const JC_FIELD parent, const char *child_name)
{
	JC_FIELD	material_field;
	t_material	material;

	material_field = jc_get_field(child_name, parent, JC_OBJ);
	material.color = parse_color(material_field, "color");
	material.specular = jc_get_float(material_field, "specular");
	return (material);
}
