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
	GTK_CHANGER_SET_VALUE(tab.transparency.change, shape_mat.transparency);
	GTK_CHANGER_SET_VALUE(tab.refraction.change, shape_mat.refraction);
	GTK_CHANGER_SET_VALUE(tab.reflective.change, shape_mat.reflective);
	GTK_CHANGER_SET_VALUE(tab.specular.change, shape_mat.specular);
}
