/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_set_triangle_dots_signals.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:28:10 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:28:10 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

void	gtk_set_triangle_dots_signals(t_transform_tab *tab, t_rt *rt)
{
	g_signal_connect(G_OBJECT(tab->dots_expander), "notify::expanded",
		G_CALLBACK(shape_expander_callback), rt);
	g_signal_connect(G_OBJECT(tab->a[0].spin), "value-changed",
		G_CALLBACK(spin_button_shape_dot_a_changer), rt);
	g_signal_connect(G_OBJECT(tab->a[1].spin), "value-changed",
		G_CALLBACK(spin_button_shape_dot_a_changer), rt);
	g_signal_connect(G_OBJECT(tab->a[2].spin), "value-changed",
		G_CALLBACK(spin_button_shape_dot_a_changer), rt);
	g_signal_connect(G_OBJECT(tab->b[0].spin), "value-changed",
		G_CALLBACK(spin_button_shape_dot_b_changer), rt);
	g_signal_connect(G_OBJECT(tab->b[1].spin), "value-changed",
		G_CALLBACK(spin_button_shape_dot_b_changer), rt);
	g_signal_connect(G_OBJECT(tab->b[2].spin), "value-changed",
		G_CALLBACK(spin_button_shape_dot_b_changer), rt);
	g_signal_connect(G_OBJECT(tab->c[0].spin), "value-changed",
		G_CALLBACK(spin_button_shape_dot_c_changer), rt);
	g_signal_connect(G_OBJECT(tab->c[1].spin), "value-changed",
		G_CALLBACK(spin_button_shape_dot_c_changer), rt);
	g_signal_connect(G_OBJECT(tab->c[2].spin), "value-changed",
		G_CALLBACK(spin_button_shape_dot_c_changer), rt);
}
