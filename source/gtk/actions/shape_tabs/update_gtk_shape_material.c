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
	gtk_range_set_value(GTK_RANGE(tab.transparency.scale),
						shape_mat.transparency);
	gtk_range_set_value(GTK_RANGE(tab.reflective.scale),
						shape_mat.reflective);
	gtk_range_set_value(GTK_RANGE(tab.specular.scale),
						shape_mat.specular);
}
