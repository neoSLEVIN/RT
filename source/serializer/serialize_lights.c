/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serialize_lights.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:32:04 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:32:04 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serializer.h"

static void	s_light_obj(t_serializer *s, LIGHT *light)
{
	s_open_obj(s);
	s_name(s, "name");
	s_str_in_quotes(s, light->name);
	s_comma(s);
	s_name(s, "type");
	s_str_in_quotes_free(s, get_light_type_name(light->dto->type));
	s_comma(s);
	s_name(s, "intensity");
	s_float(s, light->dto->intensity);
	if (light->dto->type == POINT)
	{
		s_comma(s);
		s_name(s, "position");
		s_float3(s, light->dto->position);
	}
	else if (light->dto->type == DIRECTION)
	{
		s_comma(s);
		s_name(s, "direction");
		s_float3(s, light->dto->direction);
	}
	s_close_obj(s);
}

void		s_lights_arr(t_serializer *s, LIGHT *light)
{
	s_open_arr_with_name(s, "lights");
	while (light)
	{
		s_light_obj(s, light);
		if (light->next)
			s_comma(s);
		light = light->next;
	}
	s_close_arr(s);
}
