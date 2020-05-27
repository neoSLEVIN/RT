/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_set_shape_signals.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 07:03:06 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/29 07:03:06 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

void	gtk_set_shape_signals(t_rt *rt)
{
	t_gtk_shape	*shape;

	shape = rt->gtk->ui.shape;
	g_signal_connect(G_OBJECT(shape->transform.spin_x), "value-changed",
		G_CALLBACK(spin_button_shape_position_changer), rt);
	g_signal_connect(G_OBJECT(shape->transform.spin_y), "value-changed",
		G_CALLBACK(spin_button_shape_position_changer), rt);
	g_signal_connect(G_OBJECT(shape->transform.spin_z), "value-changed",
		G_CALLBACK(spin_button_shape_position_changer), rt);
}
