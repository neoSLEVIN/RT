/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_set_textures_positions.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:27:35 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:27:36 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

void	gtk_set_textures_positions(t_gtk_textures *textures)
{
	gtk_container_add(GTK_CONTAINER(textures->expander),
					textures->scrolled_window);
	gtk_container_add(GTK_CONTAINER(textures->scrolled_window), textures->tree);
}
