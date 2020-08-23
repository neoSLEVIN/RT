/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_set_shapes_positions.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 22:43:51 by cschoen           #+#    #+#             */
/*   Updated: 2020/06/01 06:14:26 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

void	gtk_set_shapes_positions(t_gtk_shapes *shapes)
{
	gtk_container_add(GTK_CONTAINER(shapes->expander), shapes->scrolled_window);
	gtk_container_add(GTK_CONTAINER(shapes->scrolled_window), shapes->tree);
}
