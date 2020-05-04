/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_gtk.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 21:06:05 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/04 22:13:20 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

GTK_DATA	*new_gtk(t_scene *scene, t_ocl *ocl)
{
	GTK_DATA	*gtk;

	if ((gtk = g_slice_new(GTK_DATA)) == NULL)
		ft_error("Can't allocate memory");
	gtk->img.scene = scene;
	gtk->img.ocl = ocl;
	gtk_set_default_params(gtk);
	gtk_set_main_window(gtk);
	gtk_set_objects(gtk);
	gtk_set_signals(gtk);
	gtk_set_positions(gtk);
	return (gtk);
}
