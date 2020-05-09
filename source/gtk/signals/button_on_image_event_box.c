/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_on_image_event_box.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 20:06:20 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/09 20:06:20 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

gboolean	press_button_on_image_event_box(GtkWidget *event_box,
										GdkEventButton *event, gpointer data)
{
	t_rt	*rt;

	rt = (t_rt*)data;
	increase_holders_cnt(&rt->info->holders_cnt, &rt->info->w_key);
	move_cam(rt, 'w');
	return (TRUE);
}

gboolean	release_button_on_image_event_box(GtkWidget *event_box,
										GdkEventButton *event, gpointer data)
{
	t_rt	*rt;

	rt = (t_rt*)data;
	decrease_holders_cnt(&rt->info->holders_cnt, &rt->info->w_key);
	return (TRUE);
}
