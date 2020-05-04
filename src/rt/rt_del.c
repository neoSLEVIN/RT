/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_del.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 15:16:56 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/04 15:16:56 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	rt_lights_del(t_list_light **list_light)
{
	if (!list_light || !*list_light)
		return ;
	rt_lights_del(&(*list_light)->next);
	ft_memdel((void**)&(*list_light)->light);
	ft_memdel((void**)list_light);
}

void	rt_shapes_del(t_list_shape **list_shape)
{
	if (!list_shape || !*list_shape)
		return ;
	rt_shapes_del(&(*list_shape)->next);
	ft_memdel(&(*list_shape)->shape);
	ft_memdel((void**)list_shape);
}
