/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   press_key_on_window.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 20:03:34 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/30 01:08:25 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

static _Bool	do_press_key_for_camera(t_rt *rt, GdkEventKey *event)
{
	if (event->keyval == GDK_KEY_r)
		increase_holders_cnt(&rt->info->keyhold_cnt, &rt->info->r_key, rt);
	else if (event->keyval == GDK_KEY_space)
		increase_holders_cnt(&rt->info->keyhold_cnt, &rt->info->space_key, rt);
	else if (event->keyval == GDK_KEY_c)
		increase_holders_cnt(&rt->info->keyhold_cnt, &rt->info->c_key, rt);
	else if (event->keyval == GDK_KEY_w)
		increase_holders_cnt(&rt->info->keyhold_cnt, &rt->info->w_key, rt);
	else if (event->keyval == GDK_KEY_s)
		increase_holders_cnt(&rt->info->keyhold_cnt, &rt->info->s_key, rt);
	else if (event->keyval == GDK_KEY_a)
		increase_holders_cnt(&rt->info->keyhold_cnt, &rt->info->a_key, rt);
	else if (event->keyval == GDK_KEY_d)
		increase_holders_cnt(&rt->info->keyhold_cnt, &rt->info->d_key, rt);
	else if (event->keyval == GDK_KEY_q)
		increase_holders_cnt(&rt->info->keyhold_cnt, &rt->info->q_key, rt);
	else if (event->keyval == GDK_KEY_e)
		increase_holders_cnt(&rt->info->keyhold_cnt, &rt->info->e_key, rt);
	else
		return (FALSE);
	return (TRUE);
}

static _Bool	do_press_numpad_for_camera(t_rt *rt, GdkEventKey *event)
{
	if (event->keyval == GDK_KEY_KP_2)
		increase_holders_cnt(&rt->info->keyhold_cnt, &rt->info->num_2, rt);
	else if (event->keyval == GDK_KEY_KP_4)
		increase_holders_cnt(&rt->info->keyhold_cnt, &rt->info->num_4, rt);
	else if (event->keyval == GDK_KEY_KP_6)
		increase_holders_cnt(&rt->info->keyhold_cnt, &rt->info->num_6, rt);
	else if (event->keyval == GDK_KEY_KP_8)
		increase_holders_cnt(&rt->info->keyhold_cnt, &rt->info->num_8, rt);
	else if (event->keyval == GDK_KEY_KP_Decimal)
		increase_holders_cnt(&rt->info->keyhold_cnt, &rt->info->num_dec, rt);
	else
		return (FALSE);
	return (TRUE);
}

static _Bool	do_press_key_for_shape(t_rt *rt, GdkEventKey *event)
{
	if (rt->info->s_marker && rt->info->s_marker->dto)
	{
		if (event->keyval == GDK_KEY_i)
			increase_holders_cnt(&rt->info->keyhold_cnt, &rt->info->i_key, rt);
		else if (event->keyval == GDK_KEY_j)
			increase_holders_cnt(&rt->info->keyhold_cnt, &rt->info->j_key, rt);
		else if (event->keyval == GDK_KEY_k)
			increase_holders_cnt(&rt->info->keyhold_cnt, &rt->info->k_key, rt);
		else if (event->keyval == GDK_KEY_l)
			increase_holders_cnt(&rt->info->keyhold_cnt, &rt->info->l_key, rt);
		else if (event->keyval == GDK_KEY_u)
			increase_holders_cnt(&rt->info->keyhold_cnt, &rt->info->u_key, rt);
		else if (event->keyval == GDK_KEY_o)
			increase_holders_cnt(&rt->info->keyhold_cnt, &rt->info->o_key, rt);
		else
			return (FALSE);
	}
	else
		return (FALSE);
	return (TRUE);
}

static void	copy_shape(t_rt *rt)
{
	if (rt->info->s_copy && rt->info->s_marker)
	{
		ft_memdel((void**)&rt->info->s_copy->dto);
		ft_strdel(&rt->info->s_copy->name);
		ft_memdel((void**)&rt->info->s_copy);
	}
	if (rt->info->s_marker)
	{
		if (!(rt->info->s_copy = (SHAPE*)malloc(sizeof(SHAPE))))
			ft_error("Can't allocate memory");
		get_default_shape(rt->info->s_copy, NULL);
		if (!(rt->info->s_copy->dto = (DTO_SHAPE*)malloc(sizeof(DTO_SHAPE))))
			ft_error("Can't allocate memory");
		*rt->info->s_copy->dto = *rt->info->s_marker->dto;
		if (!(rt->info->s_copy->name = ft_strdup(rt->info->s_marker->name)))
			ft_error("Can't allocate memory");
	}
}

static void	update_positions(DTO_SHAPE *dto, FLT3 new_position)
{
	FLT3	diff;
	int		i;

	i = -1;
	diff = v3_sub(new_position, dto->transform.position);
	dto->transform.position = new_position;
	while (++i < SECTION_CNT)
		dto->sections[i].position = v3_add(dto->sections[i].position, diff);
}

static void	paste_shape(t_rt *rt)
{
	SHAPE	*shape;
	SHAPE	*temp;

	if (!rt->info->s_copy)
		return ;
	if (!(shape = (SHAPE*)malloc(sizeof(SHAPE))))
		ft_error("Can't allocate memory");
	get_default_shape(shape, rt->info->s_copy->dto);
	update_positions(shape->dto,
		v3_add(rt->ocl->dto.cam.origin,
			v3_scale(rt->ocl->dto.cam.forward, 50)));
	if (!(shape->name = ft_strdup(rt->info->s_copy->name)))
		ft_error("Can't allocate memory");
	if (rt->scene->shapes == NULL)
	{
		rt->scene->shapes = shape;
		return (new_shape_update_everything(rt, &rt->gtk->ui.shapes, shape));
	}
	temp = rt->scene->shapes;
	while (temp->next)
		temp = temp->next;
	temp->next = shape;
	shape->prev = temp;
	new_shape_update_everything(rt, &rt->gtk->ui.shapes, shape);
}

gboolean		press_key_on_window(GtkWidget *window, GdkEventKey *event,
									gpointer data)
{
	t_rt	*rt;

	(void)window;
	rt = (t_rt*)data;
	if (event->state == GDK_MOD1_MASK ||
			gtk_widget_is_focus(rt->gtk->ui.shape->main.name_changer) ||
			gtk_widget_is_focus(rt->gtk->ui.light->name_changer))
		return (FALSE);
	if (event->state == GDK_CONTROL_MASK &&
			(event->keyval == GDK_KEY_c || event->keyval == GDK_KEY_v))
	{
		if (event->keyval == GDK_KEY_c)
			copy_shape(rt);
		else
			paste_shape(rt);
		return (TRUE);
	}
	if (do_press_key_for_camera(rt, event) ||
		do_press_numpad_for_camera(rt, event) ||
		do_press_key_for_shape(rt, event))
	{
		rt->info->update = TRUE;
		return (TRUE);
	}
	return (FALSE);
}
