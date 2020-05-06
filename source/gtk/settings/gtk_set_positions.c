/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_set_positions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 21:45:10 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/04 23:35:16 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

void	gtk_set_positions(GTK_DATA *gtk)
{
	gtk_container_add(GTK_CONTAINER(gtk->window), gtk->h_box);
	gtk_box_pack_start(GTK_BOX(gtk->h_box), GTK_WIDGET(gtk->rt.image),
		FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(gtk->h_box), gtk->button, FALSE, FALSE, 0);
}
