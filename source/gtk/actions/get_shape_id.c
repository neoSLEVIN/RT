/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_shape_id.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/16 07:46:49 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/16 19:02:30 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

void	get_shape_id(t_rt *rt)
{
	int		i;
	SHAPE	*temp;

	if (rt->info->shape_id == -1)
		return (clear_shape_marker(rt));
	if (rt->ocl->dto.shapes[rt->info->shape_id].marker)
		return (clear_shape_marker(rt));
	i = -1;
	temp = rt->scene->shapes;
	while (temp && ++i < rt->info->shape_id)
		temp = temp->next;
	if (temp && rt->info->shape_id == i)
	{
		clear_light_marker(rt);
		clear_shape_marker(rt);
		rt->info->s_marker = temp;
		temp->dto->marker = TRUE;
	}
	else
		clear_shape_marker(rt);
}
