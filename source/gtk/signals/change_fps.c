/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_fps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 05:02:06 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/10 05:02:06 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

gboolean	change_fps(GtkWidget *window, GdkEventKey *event, gpointer data)
{
	t_rt	*rt;

	rt = (t_rt*)data;
	if ((event->keyval == '=' && (rt->scene->fps + 0.5f > 200)) ||
		(event->keyval == '-' && (rt->scene->fps - 0.5 < 0.5f)))
		return (TRUE);
	if (event->keyval == '=')
		rt->scene->fps += 0.5f;
	else if (event->keyval == '-')
		rt->scene->fps -= 0.5f;
	else
		return (FALSE);
	g_source_remove(rt->gtk->timeout_id);
	rt->gtk->timeout_id =
			g_timeout_add(1000 / rt->scene->fps, draw_by_timeout, rt);
	return (TRUE);
}
