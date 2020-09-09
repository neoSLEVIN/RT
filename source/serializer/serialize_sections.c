/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serialize_sections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:32:20 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:32:20 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serializer.h"

static void	s_section_obj(t_serializer *s, SECTION *section)
{
	s_open_obj(s);
	s_name(s, "on");
	s_bool(s, section->on);
	s_comma(s);
	s_name(s, "type");
	s_str_in_quotes(s, section->type == PLANE ? "PLANE" : "SPHERE");
	s_comma(s);
	s_name(s, "position");
	s_float3(s, section->position);
	s_comma(s);
	if (section->type == PLANE)
	{
		s_name(s, "direction");
		s_float3(s, v3_norm(section->direction));
	}
	else
	{
		s_name(s, "radius");
		s_float(s, section->param);
	}
	s_close_obj(s);
}

static void	s_sections_elements_arr(t_serializer *s, SECTION *sections)
{
	int		i;
	_Bool	first_on;

	i = -1;
	first_on = TRUE;
	s_open_arr_with_name(s, "elements");
	while (++i < SECTION_CNT)
	{
		if (sections[i].on || (i == SECTION_CNT - 1 && first_on))
		{
			if (first_on == FALSE)
				s_comma(s);
			first_on = FALSE;
			s_section_obj(s, &sections[i]);
		}
	}
	s_close_arr(s);
}

void		s_sections_obj(t_serializer *s, DTO_SHAPE *dto)
{
	s_open_obj_with_name(s, "sections");
	s_name(s, "style");
	s_str_in_quotes(s, dto->is_complex_section ? "COMPLEX" : "SIMPLE");
	s_comma(s);
	s_sections_elements_arr(s, dto->sections);
	s_close_obj(s);
}
