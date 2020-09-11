/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serialize_ppm_img.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:32:11 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:32:11 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serializer.h"

void		s_shape_texture_obj(t_serializer *s, int id, PPM_IMG *ppm)
{
	s_open_obj_with_name(s, "texture");
	s_name(s, "name");
	s_str_in_quotes_free(s, get_ppm_name_by_index(ppm, id, FALSE));
	s_close_obj(s);
}

void		s_shape_normal_map_obj(t_serializer *s, int id, PPM_IMG *ppm)
{
	s_open_obj_with_name(s, "normal map");
	s_name(s, "name");
	s_str_in_quotes_free(s, get_ppm_name_by_index(ppm, id, TRUE));
	s_close_obj(s);
}

static void	s_ppm_img_obj(t_serializer *s, PPM_IMG *ppm, const char *dir)
{
	char	*path;

	s_open_obj(s);
	s_name(s, "name");
	s_str_in_quotes(s, ppm->name);
	s_comma(s);
	s_name(s, "path");
	if (!(path = ft_strstr(ppm->path, dir)))
		ft_error("WTF");
	path += ft_strlen(dir);
	s_str_in_quotes(s, path);
	s_close_obj(s);
}

void		s_ppm_img_arr(t_serializer *s, const char *name, PPM_IMG *ppm,
							const char *dir)
{
	s_open_arr_with_name(s, name);
	while (ppm)
	{
		s_ppm_img_obj(s, ppm, dir);
		if (ppm->next)
			s_comma(s);
		ppm = ppm->next;
	}
	s_close_arr(s);
}
