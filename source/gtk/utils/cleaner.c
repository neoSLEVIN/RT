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

void	clear_lights(LIGHT **light)
{
	if (!light || !*light)
		return ;
	clear_lights(&(*light)->next);
	ft_memdel((void**)light);
}

void	clear_shapes(SHAPE **shape)
{
	if (!shape || !*shape)
		return ;
	clear_shapes(&(*shape)->next);
	ft_memdel((void**)shape);
}
