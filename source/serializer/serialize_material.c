/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serialize_material.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:32:07 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:32:08 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serializer.h"

static char	get_hex_num(int num)
{
	if (num < 0)
		ft_error("Value must be positive (get_hex_num)");
	if (num < 10)
		return ((char)('0' + num));
	return ((char)('A' + (num - 10)));
}

static char	*get_color_by_float3(FLT3 value)
{
	char	*color;

	if ((color = ft_strnew(6)) == NULL)
		ft_error("Can't allocate memory");
	color[0] = get_hex_num((int)(value.x * 255) / 16);
	color[1] = get_hex_num((int)(value.x * 255) % 16);
	color[2] = get_hex_num((int)(value.y * 255) / 16);
	color[3] = get_hex_num((int)(value.y * 255) % 16);
	color[4] = get_hex_num((int)(value.z * 255) / 16);
	color[5] = get_hex_num((int)(value.z * 255) % 16);
	return (color);
}

void		s_material_obj(t_serializer *s, MATERIAL *material)
{
	s_open_obj_with_name(s, "material");
	s_name(s, "color");
	s_str_in_quotes_free(s, get_color_by_float3(material->color));
	s_comma(s);
	s_name(s, "specular");
	s_float(s, material->specular);
	s_comma(s);
	s_name(s, "reflective");
	s_float(s, material->reflective);
	s_comma(s);
	s_name(s, "transparency");
	s_float(s, material->transparency);
	s_comma(s);
	s_name(s, "refraction");
	s_float(s, material->refraction);
	s_close_obj(s);
}
