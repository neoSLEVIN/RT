/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_on_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 20:03:34 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/14 03:33:31 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

gboolean	press_key_on_window(GtkWidget *window, GdkEventKey *event,
								gpointer data)
{
	t_rt	*rt;

	rt = (t_rt*)data;
	if (event->keyval == GDK_KEY_space)
		increase_holders_cnt(&rt->info->keyhold_cnt, &rt->info->space_key, rt);
	else if (event->keyval == GDK_KEY_c)
		increase_holders_cnt(&rt->info->keyhold_cnt, &rt->info->c_key, rt);
	else if (event->keyval == GDK_KEY_w)
		increase_holders_cnt(&rt->info->keyhold_cnt, &rt->info->w_key, rt);
	else if (event->keyval == GDK_KEY_s)
		increase_holders_cnt(&rt->info->keyhold_cnt, &rt->info->s_key, rt);
	else if (event->keyval == GDK_KEY_a)
		increase_holders_cnt(&rt->info->keyhold_cnt, &rt->info->a_key, rt);
	else if (event->keyval == GDK_KEY_d)
		increase_holders_cnt(&rt->info->keyhold_cnt, &rt->info->d_key, rt);
	else if (event->keyval == GDK_KEY_q)
		increase_holders_cnt(&rt->info->keyhold_cnt, &rt->info->q_key, rt);
	else if (event->keyval == GDK_KEY_e)
		increase_holders_cnt(&rt->info->keyhold_cnt, &rt->info->e_key, rt);
	else if (event->keyval == GDK_KEY_KP_2)
		increase_holders_cnt(&rt->info->keyhold_cnt, &rt->info->num_2, rt);
	else if (event->keyval == GDK_KEY_KP_4)
		increase_holders_cnt(&rt->info->keyhold_cnt, &rt->info->num_4, rt);
	else if (event->keyval == GDK_KEY_KP_6)
		increase_holders_cnt(&rt->info->keyhold_cnt, &rt->info->num_6, rt);
	else if (event->keyval == GDK_KEY_KP_8)
		increase_holders_cnt(&rt->info->keyhold_cnt, &rt->info->num_8, rt);
	else if (event->keyval == GDK_KEY_KP_Decimal)
		increase_holders_cnt(&rt->info->keyhold_cnt, &rt->info->num_decimal, rt);
	else
		return (FALSE);
	rt->info->update = TRUE;
	return (TRUE);
}

gboolean	release_key_on_window(GtkWidget *window, GdkEventKey *event,
								gpointer data)
{
	t_rt	*rt;

	rt = (t_rt*)data;
	if (event->keyval == GDK_KEY_BackSpace)
		keys_to_false(rt->info);
	else if (event->keyval == GDK_KEY_space && !(event->state & GDK_SHIFT_MASK))
		decrease_holders_cnt(&rt->info->keyhold_cnt, &rt->info->space_key);
	else if (event->keyval == GDK_KEY_c)
		decrease_holders_cnt(&rt->info->keyhold_cnt, &rt->info->c_key);
	else if (event->keyval == GDK_KEY_w)
		decrease_holders_cnt(&rt->info->keyhold_cnt, &rt->info->w_key);
	else if (event->keyval == GDK_KEY_s)
		decrease_holders_cnt(&rt->info->keyhold_cnt, &rt->info->s_key);
	else if (event->keyval == GDK_KEY_a)
		decrease_holders_cnt(&rt->info->keyhold_cnt, &rt->info->a_key);
	else if (event->keyval == GDK_KEY_d)
		decrease_holders_cnt(&rt->info->keyhold_cnt, &rt->info->d_key);
	else if (event->keyval == GDK_KEY_q)
		decrease_holders_cnt(&rt->info->keyhold_cnt, &rt->info->q_key);
	else if (event->keyval == GDK_KEY_e)
		decrease_holders_cnt(&rt->info->keyhold_cnt, &rt->info->e_key);
	else if (event->keyval == GDK_KEY_KP_2)
		decrease_holders_cnt(&rt->info->keyhold_cnt, &rt->info->num_2);
	else if (event->keyval == GDK_KEY_KP_4)
		decrease_holders_cnt(&rt->info->keyhold_cnt, &rt->info->num_4);
	else if (event->keyval == GDK_KEY_KP_6)
		decrease_holders_cnt(&rt->info->keyhold_cnt, &rt->info->num_6);
	else if (event->keyval == GDK_KEY_KP_8)
		decrease_holders_cnt(&rt->info->keyhold_cnt, &rt->info->num_8);
	else if (event->keyval == GDK_KEY_KP_Decimal)
		decrease_holders_cnt(&rt->info->keyhold_cnt, &rt->info->num_decimal);
	else
		return (FALSE);
	return (TRUE);
}
