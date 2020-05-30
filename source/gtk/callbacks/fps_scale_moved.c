/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps_scale_moved.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 05:02:06 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/10 06:57:52 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

void	fps_scale_moved(GtkRange *range, gpointer data)
{
	t_rt	*rt;

	rt = (t_rt*)data;
	rt->scene->fps = gtk_range_get_value(range);
	g_source_remove(rt->gtk->timeout_id);
	rt->gtk->timeout_id =
			g_timeout_add(1000 / rt->scene->fps, draw_by_timeout, rt);
}
