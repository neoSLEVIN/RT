/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/16 06:37:24 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/16 06:37:24 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INFO_H
#define INFO_H

# include "scene.h"

/*
** =============================================================================
** ============= Additional info about keys, flags, etc for UI/UX ==============
** =============================================================================
** = "update" and "keyhold_cnt" - indicate for make_action and draw_image: =====
** === "update" - when key/button was pressed once =============================
** === "keyhold_cnt" - when at least one key/button held down ==================
** =============================================================================
*/
typedef struct	s_info
{
	_Bool		update;
	int			keyhold_cnt;
	_Bool		space_key;
	_Bool		c_key;
	_Bool		w_key;
	_Bool		s_key;
	_Bool		a_key;
	_Bool		d_key;
	_Bool		q_key;
	_Bool		e_key;
	_Bool		num_2;
	_Bool		num_4;
	_Bool		num_6;
	_Bool		num_8;
	_Bool		num_decimal;
	int			mc_hold_cnt;
	_Bool		left_mc;
	_Bool		right_mc;
	_Bool		scroll_mc;
	INT2		rmc_start_pos;
	INT2		rmc_current_pos;
	INT2		lmc_start_pos;
	INT2		lmc_current_pos;
	INT2		axis;
	int			shape_id;
	LIGHT		*l_marker;
	SHAPE		*s_marker;
}				t_info;

#endif
