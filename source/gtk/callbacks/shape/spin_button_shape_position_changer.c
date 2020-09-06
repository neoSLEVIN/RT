/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spin_button_shape_position_changer.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:24:42 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:24:42 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

static void		change_position_by_widgets(FLT3 *position,
											t_transform_tab *transform)
{
	position->x = gtk_spin_button_get_value(GTK_SPIN_BUTTON(transform->x.spin));
	position->y = gtk_spin_button_get_value(GTK_SPIN_BUTTON(transform->y.spin));
	position->z = gtk_spin_button_get_value(GTK_SPIN_BUTTON(transform->z.spin));
}

static void		change_dots_with_widgets(FLT3 *dots, t_transform_tab *trans,
										FLT3 diff, DTO_SHAPE *dto)
{
	dots[0] = v3_add(dots[0], diff);
	dots[1] = v3_add(dots[1], diff);
	dots[2] = v3_add(dots[2], diff);
	if (dto->type != TRIANGLE)
		return ;
	if (!gtk_expander_get_expanded(GTK_EXPANDER(trans->dots_expander)))
		return ;
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(trans->a[0].spin), dots[0].x);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(trans->a[1].spin), dots[0].y);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(trans->a[2].spin), dots[0].z);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(trans->b[0].spin), dots[1].x);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(trans->b[1].spin), dots[1].y);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(trans->b[2].spin), dots[1].z);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(trans->c[0].spin), dots[2].x);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(trans->c[1].spin), dots[2].y);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(trans->c[2].spin), dots[2].z);
}

static gboolean	spin_button_shape_position_changer_safe(gpointer data)
{
	int				i;
	t_rt			*rt;
	FLT3			*position;
	FLT3			temp_position;
	t_transform_tab	*transform;

	rt = (t_rt*)data;
	ASSERT_SHAPE(rt->gtk->ui.shape->shape);
	position = &rt->gtk->ui.shape->shape->dto->transform.position;
	temp_position = *position;
	transform = &rt->gtk->ui.shape->transform;
	change_position_by_widgets(position, transform);
	temp_position = v3_sub(*position, temp_position);
	change_dots_with_widgets(rt->gtk->ui.shape->shape->dto->transform.dots,
					transform, temp_position, rt->gtk->ui.shape->shape->dto);
	i = -1;
	while (++i < SECTION_CNT)
	{
		position = &rt->gtk->ui.shape->shape->dto->sections[i].position;
		*position = v3_add(*position, temp_position);
	}
	update_flags(&rt->info->update_shapes, &rt->info->update);
	update_shapes_arg(rt->ocl, &rt->info->update_s_cnt,
					&rt->info->update_shapes);
	return (FALSE);
}

void			spin_button_shape_position_changer(GtkSpinButton *button,
												gpointer data)
{
	(void)button;
	g_idle_add(spin_button_shape_position_changer_safe, data);
}
