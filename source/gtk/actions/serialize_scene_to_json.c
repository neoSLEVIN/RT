/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serialize_scene_to_json.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:22:34 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:22:34 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

gboolean	serialize_scene_to_json(gpointer data)
{
	t_rt	*rt;

	rt = (t_rt*)data;
	s_json_obj(rt->info->scene_filename, rt->scene);
	return (FALSE);
}
