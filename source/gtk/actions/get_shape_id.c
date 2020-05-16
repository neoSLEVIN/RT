/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_shape_id.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/16 07:46:49 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/16 07:55:49 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

void	get_shape_id(t_rt *rt)
{
	int		i;
	SHAPE	*temp;

	if (rt->info->s_marker && rt->info->s_marker->index == rt->info->shape_id)
		return ;
	i = -1;
	temp = rt->scene->shapes;
	while (++i < rt->scene->s_cnt && temp)
	{
		if (temp->index == rt->info->shape_id)
		{
			rt->info->l_marker = NULL;
			rt->info->s_marker = temp;
			temp->dto.marker = 1;
			rt->ocl->dto.shapes[temp->index].marker = 1;
			return ;
		}
		temp = temp->next;
	}
	clear_shape_marker(rt);
}
