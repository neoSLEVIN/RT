/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_set_material_tab_widgets.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:29:04 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:29:05 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

void	gtk_set_material_tab_widgets(t_material_tab *material_tab,
												MATERIAL *shape_material)
{
	material_tab->label = gtk_label_new("Material");
	material_tab->grid = gtk_grid_new();
	material_tab->transparency =
		gtk_set_spinner_float("Transparency:", (FLT2){0, 1},
			shape_material->transparency, 0.005);
	material_tab->refraction =
		gtk_set_spinner_float("Refraction:", (FLT2){0, 1},
								shape_material->transparency, 0.005);
	material_tab->reflective =
		gtk_set_spinner_float("Reflective:", (FLT2){0, 1},
				shape_material->reflective, 0.005);
	material_tab->specular =
		gtk_set_spinner_float("Specular:", (FLT2){0, 1},
				shape_material->specular, 0.005);
}
