/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_set_shape_color_positions.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:26:49 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:26:49 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

void	gtk_set_shape_color_positions(t_color_tab *color,
									t_texture_tab *texture)
{
	gtk_container_add(GTK_CONTAINER(color->scrolled_window), color->v_box);
	gtk_box_pack_start(GTK_BOX(color->v_box), texture->grid,
						FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(color->v_box), color->color,
						FALSE, FALSE, 0);
}
