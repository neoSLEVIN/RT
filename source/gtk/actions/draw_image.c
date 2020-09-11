/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/29 02:03:00 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

static gboolean	compute_draw(gpointer data)
{
	t_rt	*rt;

	rt = (t_rt*)data;
	gtk_window_set_title(GTK_WINDOW(rt->gtk->window), rt->gtk->titles[1]);
	run_cl(rt->ocl);
	compute_filter(rt);
	gtk_image_set_from_pixbuf(GTK_IMAGE(rt->gtk->img.image),
								rt->gtk->img.pixbuf);
	gtk_window_set_title(GTK_WINDOW(rt->gtk->window), rt->gtk->titles[0]);
	return (FALSE);
}

void			draw_image(t_rt *rt)
{
	g_idle_add(compute_draw, rt);
}
