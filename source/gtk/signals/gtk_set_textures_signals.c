/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_set_textures_signals.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:28:06 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:28:07 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

void	gtk_set_textures_signals(t_rt *rt)
{
	g_signal_connect(G_OBJECT(rt->gtk->ui.texture.tree),
		"button-press-event", G_CALLBACK(texture_tree_single_click), rt);
	g_signal_connect(G_OBJECT(rt->gtk->ui.normals.tree),
		"button-press-event", G_CALLBACK(normal_map_tree_single_click), rt);
}
