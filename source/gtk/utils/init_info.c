/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/17 16:17:48 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

void	keys_to_false(t_info *info)
{
	info->keyhold_cnt = 0;
	info->space_key = FALSE;
	info->c_key = FALSE;
	info->w_key = FALSE;
	info->s_key = FALSE;
	info->a_key = FALSE;
	info->d_key = FALSE;
	info->q_key = FALSE;
	info->e_key = FALSE;
	info->i_key = FALSE;
	info->j_key = FALSE;
	info->k_key = FALSE;
	info->l_key = FALSE;
	info->u_key = FALSE;
	info->o_key = FALSE;
	info->num_2 = FALSE;
	info->num_4 = FALSE;
	info->num_6 = FALSE;
	info->num_8 = FALSE;
	info->num_dec = FALSE;
}

void	mouse_to_false(t_info *info)
{
	info->mc_hold_cnt = 0;
	info->left_mc = FALSE;
	info->right_mc = FALSE;
	info->scroll_mc = FALSE;
	info->rmc_start_pos = (cl_int2){-1, -1};
	info->rmc_current_pos = (cl_int2){-1, -1};
	info->lmc_start_pos = (cl_int2){-1, -1};
	info->lmc_current_pos = (cl_int2){-1, -1};
	info->scroll_cnt = 0;
}

void	init_info(t_info **info)
{
	if (!(*info = (t_info*)malloc(sizeof(t_info))))
		ft_error("Can't allocate memory");
	(*info)->update = TRUE;
	(*info)->update_cam = FALSE;
	(*info)->update_shapes = FALSE;
	(*info)->update_s_cnt = FALSE;
	keys_to_false(*info);
	mouse_to_false(*info);
	(*info)->axis = (INT2){-1, -1};
	(*info)->shape_id = -1;
	(*info)->l_marker = NULL;
	(*info)->s_marker = NULL;
}
