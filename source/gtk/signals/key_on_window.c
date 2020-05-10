/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_on_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 20:03:34 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/10 07:24:12 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

gboolean	press_key_on_window(GtkWidget *window, GdkEventKey *event,
								gpointer data)
{
	t_rt	*rt;

	rt = (t_rt*)data;
	if (event->keyval == 'w')
		increase_holders_cnt(&rt->info->holders_cnt, &rt->info->w_key, rt);
	else if (event->keyval == 's')
		increase_holders_cnt(&rt->info->holders_cnt, &rt->info->s_key, rt);
	else if (event->keyval == 'a')
		increase_holders_cnt(&rt->info->holders_cnt, &rt->info->a_key, rt);
	else if (event->keyval == 'd')
		increase_holders_cnt(&rt->info->holders_cnt, &rt->info->d_key, rt);
	else if (event->keyval == 'q')
		increase_holders_cnt(&rt->info->holders_cnt, &rt->info->q_key, rt);
	else if (event->keyval == 'e')
		increase_holders_cnt(&rt->info->holders_cnt, &rt->info->e_key, rt);
	else if (event->keyval == GDK_KEY_KP_2)
		increase_holders_cnt(&rt->info->holders_cnt, &rt->info->num_2, rt);
	else if (event->keyval == GDK_KEY_KP_4)
		increase_holders_cnt(&rt->info->holders_cnt, &rt->info->num_4, rt);
	else if (event->keyval == GDK_KEY_KP_6)
		increase_holders_cnt(&rt->info->holders_cnt, &rt->info->num_6, rt);
	else if (event->keyval == GDK_KEY_KP_8)
		increase_holders_cnt(&rt->info->holders_cnt, &rt->info->num_8, rt);
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
	if (event->keyval == 'w')
		decrease_holders_cnt(&rt->info->holders_cnt, &rt->info->w_key);
	else if (event->keyval == 's')
		decrease_holders_cnt(&rt->info->holders_cnt, &rt->info->s_key);
	else if (event->keyval == 'a')
		decrease_holders_cnt(&rt->info->holders_cnt, &rt->info->a_key);
	else if (event->keyval == 'd')
		decrease_holders_cnt(&rt->info->holders_cnt, &rt->info->d_key);
	else if (event->keyval == 'q')
		decrease_holders_cnt(&rt->info->holders_cnt, &rt->info->q_key);
	else if (event->keyval == 'e')
		decrease_holders_cnt(&rt->info->holders_cnt, &rt->info->e_key);
	else if (event->keyval == GDK_KEY_KP_2)
		decrease_holders_cnt(&rt->info->holders_cnt, &rt->info->num_2);
	else if (event->keyval == GDK_KEY_KP_4)
		decrease_holders_cnt(&rt->info->holders_cnt, &rt->info->num_4);
	else if (event->keyval == GDK_KEY_KP_6)
		decrease_holders_cnt(&rt->info->holders_cnt, &rt->info->num_6);
	else if (event->keyval == GDK_KEY_KP_8)
		decrease_holders_cnt(&rt->info->holders_cnt, &rt->info->num_8);
	else
		return (FALSE);
	return (TRUE);
}
