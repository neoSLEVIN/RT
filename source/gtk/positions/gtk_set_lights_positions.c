/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_set_lights_positions.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:27:24 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:27:24 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

void	gtk_set_lights_positions(t_gtk_lights *lights)
{
	gtk_container_add(GTK_CONTAINER(lights->expander), lights->scrolled_window);
	gtk_container_add(GTK_CONTAINER(lights->scrolled_window), lights->tree);
}
