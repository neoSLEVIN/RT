/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/09 15:30:54 by cschoen          ###   ########.fr       */
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
