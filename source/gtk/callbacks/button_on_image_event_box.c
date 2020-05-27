/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_on_image_event_box.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 20:06:20 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/29 01:41:56 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

static void	action_for_left_mouse_click(t_rt *rt, GdkEventButton *event)
{
	if (event->type == GDK_DOUBLE_BUTTON_PRESS)
	{
		clear_shape_marker(rt);
		update_shapes_arg(rt->ocl, &rt->info->update_s_cnt,
						&rt->info->update_shapes);
	}
	else
	{
		rt->info->lmc_start_pos = (cl_int2){event->x, event->y};
		rt->info->lmc_current_pos = (cl_int2){event->x, event->y};
		update_cursor_arg(rt->ocl);
		run_cl(rt->ocl);
		get_shape_id(rt);
		update_shapes_arg(rt->ocl, &rt->info->update_s_cnt,
						&rt->info->update_shapes);
		increase_holders_cnt(&rt->info->mc_hold_cnt, &rt->info->left_mc, rt);
	}
}

gboolean	press_button_on_image_event_box(GtkWidget *event_box,
										GdkEventButton *event, gpointer data)
{
	t_rt	*rt;

	(void)event_box;
	rt = (t_rt*)data;
	if (event->button == 1)
		action_for_left_mouse_click(rt, event);
	else if (event->button == 2)
		increase_holders_cnt(&rt->info->mc_hold_cnt, &rt->info->scroll_mc, rt);
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

	(void)event_box;
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

	(void)event_box;
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

gboolean	scroll_on_image_event_box(GtkWidget *event_box, GdkEvent *event,
										gpointer data)
{
	t_rt	*rt;

	(void)event_box;
	rt = (t_rt*)data;
	if (!rt->info->s_marker || !rt->info->s_marker->dto)
		rt->info->scroll_cnt = 0;
	else if (event->type == GDK_SCROLL)
	{
		if (event->scroll.direction == GDK_SCROLL_DOWN)
			rt->info->scroll_cnt = -1;
		if (event->scroll.direction == GDK_SCROLL_UP)
			rt->info->scroll_cnt = 1;
	}
	else
		return (TRUE);
	rt->info->update = TRUE;
	return (FALSE);
}
