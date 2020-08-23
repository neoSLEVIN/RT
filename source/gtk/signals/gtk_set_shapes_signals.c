/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_set_shapes_signals.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 06:50:38 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/29 06:50:38 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

void	gtk_set_shapes_signals(t_rt *rt)
{
	g_signal_connect(G_OBJECT(rt->gtk->ui.shapes.select),
		"changed", G_CALLBACK(shapes_tree_selection_changer), rt);
	g_signal_connect(G_OBJECT(rt->gtk->ui.shapes.tree),
		"row-activated", G_CALLBACK(shapes_tree_double_click), rt);
	g_signal_connect(G_OBJECT(rt->gtk->ui.shapes.tree),
		"button-press-event", G_CALLBACK(shapes_tree_single_click), rt);
}
