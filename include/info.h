/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/16 06:37:24 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/17 16:17:48 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INFO_H
# define INFO_H

# include "scene.h"

/*
** =============================================================================
** ============= Additional info about keys, flags, etc for UI/UX ==============
** =============================================================================
** = "update" and "keyhold_cnt" - indicate for make_action and draw_image: =====
** === "update" - when key/button was pressed once =============================
** === "keyhold_cnt" - when at least one key held down =========================
** =============================================================================
*/
typedef struct	s_info
{
	_Bool		update;
	_Bool		update_cam;
	_Bool		update_s_name;
	_Bool		update_s_main;
	_Bool		update_s_pos;
	_Bool		update_s_mat;
	_Bool		update_s_col;
	_Bool		update_s_tex;
	_Bool		update_s_sec;
	_Bool		update_s_param;
	_Bool		update_shapes;
	_Bool		update_s_cnt;
	_Bool		update_lights;
	_Bool		update_l_cnt;
	_Bool		update_l_name;
	_Bool		update_l_params;
	_Bool		update_off_points;
	int			keyhold_cnt;
	_Bool		space_key;
	_Bool		c_key;
	_Bool		w_key;
	_Bool		s_key;
	_Bool		a_key;
	_Bool		d_key;
	_Bool		q_key;
	_Bool		e_key;
	_Bool		i_key;
	_Bool		j_key;
	_Bool		k_key;
	_Bool		l_key;
	_Bool		u_key;
	_Bool		o_key;
	_Bool		r_key;
	_Bool		num_2;
	_Bool		num_4;
	_Bool		num_6;
	_Bool		num_8;
	_Bool		num_dec;
	int			mc_hold_cnt;
	_Bool		left_mc;
	_Bool		right_mc;
	_Bool		scroll_mc;
	int			scroll_cnt;
	INT2		rmc_start_pos;
	INT2		rmc_current_pos;
	INT2		lmc_start_pos;
	INT2		lmc_current_pos;
	INT2		axis;
	int			shape_id;
	SHAPE		*s_marker;
	SHAPE		*s_copy;
	DTO_SHAPE	default_shape_dto;
	DTO_LIGHT	default_light_dto;
	char		*image_filename;
	char		*scene_filename;
}				t_info;

#endif
