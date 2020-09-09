/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_set_transform_tab_widgets.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:29:18 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:29:18 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

static void	gtk_set_label_properties(GtkWidget **label, const char *name)
{
	*label = gtk_label_new(name);
	gtk_widget_set_margin_top(*label, 5);
	gtk_widget_set_margin_bottom(*label, 5);
}

static void	gtk_set_dots_widgets(t_transform_tab *tab, FLT3 *dots)
{
	tab->dots_expander = gtk_expander_new("Triangle dots");
	tab->dots_grid = gtk_grid_new();
	gtk_set_label_properties(&tab->a[0].label, "A:");
	gtk_set_label_properties(&tab->b[0].label, "B:");
	gtk_set_label_properties(&tab->c[0].label, "C:");
	gtk_set_spin_button_for_float(&tab->a[0].spin, dots[0].x);
	gtk_set_spin_button_for_float(&tab->a[1].spin, dots[0].y);
	gtk_set_spin_button_for_float(&tab->a[2].spin, dots[0].z);
	gtk_set_spin_button_for_float(&tab->b[0].spin, dots[1].x);
	gtk_set_spin_button_for_float(&tab->b[1].spin, dots[1].y);
	gtk_set_spin_button_for_float(&tab->b[2].spin, dots[1].z);
	gtk_set_spin_button_for_float(&tab->c[0].spin, dots[2].x);
	gtk_set_spin_button_for_float(&tab->c[1].spin, dots[2].y);
	gtk_set_spin_button_for_float(&tab->c[2].spin, dots[2].z);
}

void		gtk_set_transform_tab_widgets(t_transform_tab *tab,
						TRANSFORM *shape_transform)
{
	tab->label = gtk_label_new("Transform");
	tab->v_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	tab->pos_grid = gtk_grid_new();
	gtk_set_label_properties(&tab->label_pos, "Position:");
	tab->x.label = gtk_label_new("X:");
	gtk_widget_set_margin_start(tab->x.label, 5);
	gtk_widget_set_margin_end(tab->x.label, 5);
	gtk_set_spin_button_for_float(&tab->x.spin, shape_transform->position.x);
	tab->y.label = gtk_label_new("Y:");
	gtk_set_spin_button_for_float(&tab->y.spin, shape_transform->position.y);
	tab->z.label = gtk_label_new("Z:");
	gtk_set_spin_button_for_float(&tab->z.spin, shape_transform->position.z);
	gtk_set_dots_widgets(tab, shape_transform->dots);
}
