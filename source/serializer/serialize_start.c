/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serialize_start.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:32:27 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:32:28 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serializer.h"

void	s_json_obj(const char *scene_filename, SCENE *scene)
{
	t_serializer	s;

	s_open_serializer(&s, scene_filename);
	s_open_obj_no_indent(&s);
	s_settings_obj(&s, scene);
	s_comma(&s);
	s_scene_obj(&s, scene);
	s_close_obj(&s);
	s_close_serializer(&s);
}
