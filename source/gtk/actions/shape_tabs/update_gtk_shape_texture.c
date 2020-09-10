/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_gtk_shape_texture.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:21:24 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:21:25 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

void	update_gtk_shape_texture(t_texture_tab tab,
								int texture_id, int normal_map_id)
{
	gtk_combo_box_set_active(GTK_COMBO_BOX(tab.texture_combo),
							texture_id + 5);
	gtk_combo_box_set_active(GTK_COMBO_BOX(tab.normals_combo),
							normal_map_id + 1);
}
