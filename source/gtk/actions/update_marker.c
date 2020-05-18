/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_marker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/16 07:52:50 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/17 18:33:51 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

void	update_shape_marker(t_rt *rt, SHAPE *shape)
{
	if (rt->info->s_marker && rt->info->s_marker->dto)
		rt->info->s_marker->dto->marker = FALSE;
	rt->info->s_marker = shape;
	if (shape && shape->dto)
		shape->dto->marker = TRUE;
}

void	clear_shape_marker(t_rt *rt)
{
	rt->info->scroll_cnt = 0;
	decrease_holders_cnt(&rt->info->keyhold_cnt, &rt->info->i_key);
	decrease_holders_cnt(&rt->info->keyhold_cnt, &rt->info->j_key);
	decrease_holders_cnt(&rt->info->keyhold_cnt, &rt->info->k_key);
	decrease_holders_cnt(&rt->info->keyhold_cnt, &rt->info->l_key);
	decrease_holders_cnt(&rt->info->keyhold_cnt, &rt->info->u_key);
	decrease_holders_cnt(&rt->info->keyhold_cnt, &rt->info->o_key);
	if (rt->info->s_marker && rt->info->s_marker->dto)
		rt->info->s_marker->dto->marker = FALSE;
	rt->info->s_marker = NULL;
}

void	clear_light_marker(t_rt *rt)
{
	if (rt->info->l_marker && rt->info->l_marker->dto)
		rt->info->l_marker->dto->marker = FALSE;
	rt->info->l_marker = NULL;
}
