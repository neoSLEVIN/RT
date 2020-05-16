/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_on_image_event_box.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 20:06:20 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/16 07:52:46 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

gboolean	press_button_on_image_event_box(GtkWidget *event_box,
										GdkEventButton *event, gpointer data)
{
	t_rt	*rt;

	rt = (t_rt*)data;
	if (event->button == 1)
	{
		rt->info->lmc_start_pos = (cl_int2){event->x, event->y};
		rt->info->lmc_current_pos = (cl_int2){event->x, event->y};
		update_cursor(rt);
		draw_image(rt);
		get_shape_id(rt);
		update_shapes(rt, FALSE);
		increase_holders_cnt(&rt->info->mc_hold_cnt, &rt->info->left_mc, rt);
	}
	else if (event->button == 2)
	{
		increase_holders_cnt(&rt->info->mc_hold_cnt, &rt->info->scroll_mc, rt);
		decrease_holders_cnt(&rt->info->mc_hold_cnt, &rt->info->scroll_mc);
	}
	else if (event->button == 3)
	{
		rt->info->rmc_start_pos = (cl_int2){event->x, event->y};
		rt->info->rmc_current_pos = (cl_int2){event->x, event->y};
		increase_holders_cnt(&rt->info->mc_hold_cnt, &rt->info->right_mc, rt);
	}
	else
		return (FALSE);
	rt->info->update = TRUE;
	return (TRUE);
}

gboolean	motion_button_on_image_event_box(GtkWidget *event_box,
										GdkEventMotion *event, gpointer data)
{
	t_rt	*rt;

	rt = (t_rt*)data;
	if (rt->info->right_mc)
		rt->info->rmc_current_pos = (INT2){event->x, event->y};
	else if (rt->info->left_mc)
		rt->info->lmc_current_pos = (INT2){event->x, event->y};
	else
		return (FALSE);
	rt->info->update = TRUE;
	return (TRUE);
}

gboolean	release_button_on_image_event_box(GtkWidget *event_box,
										GdkEventButton *event, gpointer data)
{
	t_rt	*rt;

	rt = (t_rt*)data;
	if (event->button == 1)
		decrease_holders_cnt(&rt->info->mc_hold_cnt, &rt->info->left_mc);
	else if (event->button == 2)
		decrease_holders_cnt(&rt->info->mc_hold_cnt, &rt->info->scroll_mc);
	else if (event->button == 3)
		decrease_holders_cnt(&rt->info->mc_hold_cnt, &rt->info->right_mc);
	else
		return (FALSE);
	return (TRUE);
}
