/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_set_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/09 20:08:02 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

static void		make_action(t_rt *rt)
{
	if (rt->info->w_key)
		move_cam(rt, 'w');
	if (rt->info->s_key)
		move_cam(rt, 's');
	if (rt->info->a_key)
		move_cam(rt, 'a');
	if (rt->info->d_key)
		move_cam(rt, 'd');
	if (rt->info->q_key)
		move_cam(rt, 'q');
	if (rt->info->e_key)
		move_cam(rt, 'e');
}

static int		draw_by_timeout(gpointer data)
{
	t_rt	*rt;

	rt = (t_rt*)data;
	if (rt->info->holders_cnt != 0 || rt->info->update == TRUE)
	{
		rt->info->update = FALSE;
		make_action(rt);
		draw_image(rt);
	}
	return (TRUE);
}

void			gtk_set_signals(t_rt *rt)
{
	g_signal_connect(G_OBJECT(rt->gtk->window), "key-press_event",
					G_CALLBACK(escape_window), NULL);
	g_signal_connect(G_OBJECT(rt->gtk->window), "key-press_event",
					G_CALLBACK(press_key_on_window), rt);
	g_signal_connect(G_OBJECT(rt->gtk->window), "key-release_event",
					G_CALLBACK(release_key_on_window), rt);
	g_signal_connect(G_OBJECT(rt->gtk->image_event_box), "button-press-event",
					G_CALLBACK(press_button_on_image_event_box), rt);
	g_signal_connect(G_OBJECT(rt->gtk->image_event_box), "button-release-event",
					G_CALLBACK(release_button_on_image_event_box), rt);
//	g_signal_connect(G_OBJECT(rt->gtk->button), "pressed",
//		G_CALLBACK(signal_on_window), rt);
	g_timeout_add(1000 / FPS, draw_by_timeout, rt);
}
