/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   release_key_on_window.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 01:14:23 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/18 01:14:23 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

static gboolean	do_release_key_for_camera(t_rt *rt, GdkEventKey *event)
{
	if (event->keyval == GDK_KEY_r)
		decrease_holders_cnt(&rt->info->keyhold_cnt, &rt->info->r_key);
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
	else
		return (FALSE);
	return (TRUE);
}

static gboolean	do_release_numpad_for_camera(t_rt *rt, GdkEventKey *event)
{
	if (event->keyval == GDK_KEY_KP_2)
		decrease_holders_cnt(&rt->info->keyhold_cnt, &rt->info->num_2);
	else if (event->keyval == GDK_KEY_KP_4)
		decrease_holders_cnt(&rt->info->keyhold_cnt, &rt->info->num_4);
	else if (event->keyval == GDK_KEY_KP_6)
		decrease_holders_cnt(&rt->info->keyhold_cnt, &rt->info->num_6);
	else if (event->keyval == GDK_KEY_KP_8)
		decrease_holders_cnt(&rt->info->keyhold_cnt, &rt->info->num_8);
	else if (event->keyval == GDK_KEY_KP_Decimal)
		decrease_holders_cnt(&rt->info->keyhold_cnt, &rt->info->num_dec);
	else
		return (FALSE);
	return (TRUE);
}

static gboolean	do_release_key_for_shape(t_rt *rt, GdkEventKey *event)
{
	if (event->keyval == GDK_KEY_i)
		decrease_holders_cnt(&rt->info->keyhold_cnt, &rt->info->i_key);
	else if (event->keyval == GDK_KEY_j)
		decrease_holders_cnt(&rt->info->keyhold_cnt, &rt->info->j_key);
	else if (event->keyval == GDK_KEY_k)
		decrease_holders_cnt(&rt->info->keyhold_cnt, &rt->info->k_key);
	else if (event->keyval == GDK_KEY_l)
		decrease_holders_cnt(&rt->info->keyhold_cnt, &rt->info->l_key);
	else if (event->keyval == GDK_KEY_u)
		decrease_holders_cnt(&rt->info->keyhold_cnt, &rt->info->u_key);
	else if (event->keyval == GDK_KEY_o)
		decrease_holders_cnt(&rt->info->keyhold_cnt, &rt->info->o_key);
	else
		return (FALSE);
	return (TRUE);
}

gboolean		release_key_on_window(GtkWidget *window, GdkEventKey *event,
									gpointer data)
{
	t_rt	*rt;

	(void)window;
	rt = (t_rt*)data;
	if (event->keyval == GDK_KEY_BackSpace)
	{
		keys_to_false(rt->info);
		return (TRUE);
	}
	return (do_release_key_for_camera(rt, event) ||
			do_release_numpad_for_camera(rt, event) ||
			do_release_key_for_shape(rt, event));
}
