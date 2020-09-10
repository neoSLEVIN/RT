/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_gtk_shape_position.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:21:19 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:21:19 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

void	update_gtk_shape_position(t_transform_tab tab, DTO_SHAPE *dto)
{
	FLT3	*dots;
	FLT3	*pos;

	dots = dto->transform.dots;
	pos = &dto->transform.position;
	gtk_widget_set_visible(tab.dots_expander, dto->type == TRIANGLE);
	if (dto->type == TRIANGLE &&
		gtk_expander_get_expanded(GTK_EXPANDER(tab.dots_expander)))
	{
		gtk_spin_button_set_value(GTK_SPIN_BUTTON(tab.a[0].spin), dots[0].x);
		gtk_spin_button_set_value(GTK_SPIN_BUTTON(tab.a[1].spin), dots[0].y);
		gtk_spin_button_set_value(GTK_SPIN_BUTTON(tab.a[2].spin), dots[0].z);
		gtk_spin_button_set_value(GTK_SPIN_BUTTON(tab.b[0].spin), dots[1].x);
		gtk_spin_button_set_value(GTK_SPIN_BUTTON(tab.b[1].spin), dots[1].y);
		gtk_spin_button_set_value(GTK_SPIN_BUTTON(tab.b[2].spin), dots[1].z);
		gtk_spin_button_set_value(GTK_SPIN_BUTTON(tab.c[0].spin), dots[2].x);
		gtk_spin_button_set_value(GTK_SPIN_BUTTON(tab.c[1].spin), dots[2].y);
		gtk_spin_button_set_value(GTK_SPIN_BUTTON(tab.c[2].spin), dots[2].z);
	}
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(tab.x.spin), pos->x);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(tab.y.spin), pos->y);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(tab.z.spin), pos->z);
}
