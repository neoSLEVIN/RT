/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_gtk_shape_material.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:21:16 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:21:16 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

void	update_gtk_shape_material(t_material_tab tab, MATERIAL shape_mat)
{
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(tab.transparency.spin),
						shape_mat.transparency);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(tab.refraction.spin),
						shape_mat.refraction);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(tab.reflective.spin),
						shape_mat.reflective);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(tab.specular.spin),
						shape_mat.specular);
}
