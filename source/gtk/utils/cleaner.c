/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 15:16:56 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/05 07:16:12 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

void	clear_lights(LIGHT_LIST **list_light)
{
	if (!list_light || !*list_light)
		return ;
	clear_lights(&(*list_light)->next);
	ft_memdel((void**)&(*list_light)->light);
	ft_memdel((void**)list_light);
}

void	clear_shapes(SHAPE_LIST **list_shape)
{
	if (!list_shape || !*list_shape)
		return ;
	clear_shapes(&(*list_shape)->next);
	ft_memdel(&(*list_shape)->shape);
	ft_memdel((void**)list_shape);
}
