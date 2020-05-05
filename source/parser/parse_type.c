/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 17:57:09 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/05 07:37:29 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

LIGHT_TYPE	parse_light_type(const JC_FIELD parent, const char *child_name)
{
	char		*str_type;
	LIGHT_TYPE	type;

	str_type = ft_str_to_upper(jc_get_string(parent, child_name, FALSE));
	if (ft_strequ(str_type, "AMBIENT"))
		type = AMBIENT;
	else if (ft_strequ(str_type, "POINT"))
		type = POINT;
	else if (ft_strequ(str_type, "DIRECTION"))
		type = DIRECTION;
	else
		parse_error(jc_full_name(parent), child_name,
			" Incorrect type of light.\n\t"
				"Allowed types: [AMBIENT, POINT, DIRECTION]");
	ft_strdel(&str_type);
	return (type);
}

SHAPE_TYPE	parse_shape_type(const JC_FIELD parent, const char *child_name)
{
	char		*str_type;
	SHAPE_TYPE	type;

	str_type = ft_str_to_upper(jc_get_string(parent, child_name, FALSE));
	if (ft_strequ(str_type, "PLANE"))
		type = PLANE;
	else if (ft_strequ(str_type, "SPHERE"))
		type = SPHERE;
	else if (ft_strequ(str_type, "CONE"))
		type = CONE;
	else if (ft_strequ(str_type, "CYLINDER"))
		type = CYLINDER;
	else
		parse_error(jc_full_name(parent), child_name,
			" Incorrect type of shape.\n\t"
				"Allowed types: [PLANE, SPHERE, CONE, CYLINDER]");
	ft_strdel(&str_type);
	return (type);
}