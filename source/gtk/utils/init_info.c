/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/13 20:55:19 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

void	keys_to_false(t_info *info)
{
	info->holders_cnt = 0;
	info->space_key = FALSE;
	info->c_key = FALSE;
	info->w_key = FALSE;
	info->s_key = FALSE;
	info->a_key = FALSE;
	info->d_key = FALSE;
	info->q_key = FALSE;
	info->e_key = FALSE;
	info->num_2 = FALSE;
	info->num_4 = FALSE;
	info->num_6 = FALSE;
	info->num_8 = FALSE;
	info->num_decimal = FALSE;
}

void	init_info(t_info **info)
{
	if (!(*info = (t_info*)malloc(sizeof(t_info))))
		ft_error("Can't allocate memory");
	(*info)->update = TRUE;
	keys_to_false(*info);
	(*info)->mouse_x = -1;
	(*info)->mouse_y = -1;
	(*info)->l_marker = NULL;
	(*info)->s_marker = NULL;
}
