/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serialize_settings.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:32:23 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:32:23 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serializer.h"

static void	s_filter_param(t_serializer *s, FLT3 params, FILTER filter)
{
	if (filter == BLUR)
	{
		s_comma(s);
		s_name(s, "blur");
		s_int(s, (int)params.x);
	}
	else if (filter == SEPIA)
	{
		s_comma(s);
		s_name(s, "sepia");
		s_int(s, (int)params.y);
	}
	else if (filter == NOISE)
	{
		s_comma(s);
		s_name(s, "noise");
		s_int(s, (int)params.z);
	}
}

void		s_settings_obj(t_serializer *s, SCENE *scene)
{
	s_open_obj_with_name(s, "settings");
	s_name(s, "step");
	s_float(s, scene->step);
	s_comma(s);
	s_name(s, "angle");
	s_float(s, rad_to_deg(scene->angle));
	s_comma(s);
	s_name(s, "mirror");
	s_int(s, scene->mirror);
	s_comma(s);
	s_name(s, "anti-aliasing");
	s_bool(s, (_Bool)scene->anti_aliasing);
	s_comma(s);
	s_name(s, "filter");
	s_str_in_quotes_free(s, get_filter_type_name(scene->filter));
	s_filter_param(s, scene->filter_params, scene->filter);
	s_close_obj(s);
}
