/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_set_changer_widgets.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:29:39 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:29:39 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

t_changer	gtk_set_changer_float(const char *label, FLT2 range, cl_float value,
								cl_float step)
{
	t_changer		changer;
	GtkAdjustment	*adj;

	changer.label = gtk_label_new(label);
	gtk_widget_set_margin_start(changer.label, 5);
	gtk_widget_set_margin_top(changer.label, 5);
	adj = gtk_adjustment_new(value, range.x, range.y, step, range.y / 10, 0);
	if (IS_APPLE)
	{
		gtk_widget_set_margin_end(changer.label, 5);
		changer.change = gtk_spin_button_new(adj, step, 3);
		gtk_entry_set_width_chars(GTK_ENTRY(changer.change), 6);
		gtk_spin_button_set_numeric(GTK_SPIN_BUTTON(changer.change), TRUE);
	}
	else
	{
		gtk_widget_set_hexpand(changer.label, FALSE);
		changer.change = gtk_scale_new(GTK_ORIENTATION_HORIZONTAL, adj);
		gtk_scale_set_digits(GTK_SCALE(changer.change), 3);
		gtk_widget_set_hexpand(changer.change, TRUE);
	}
	gtk_widget_set_margin_top(changer.change, 5);
	return (changer);
}

void		gtk_set_changer(t_changer *changer, INT2 range, int value,
							const char *label)
{
	GtkAdjustment	*adj;

	changer->label = gtk_label_new(label);
	adj = gtk_adjustment_new(value, range.x, range.y, 1, range.y / 10, 0);
	if (IS_APPLE)
	{
		gtk_widget_set_margin_start(changer->label, 5);
		gtk_widget_set_margin_end(changer->label, 5);
		gtk_widget_set_margin_top(changer->label, 5);
		changer->change = gtk_spin_button_new(adj, 1, 0);
		gtk_entry_set_width_chars(GTK_ENTRY(changer->change), 5);
		gtk_spin_button_set_numeric(GTK_SPIN_BUTTON(changer->change), TRUE);
		gtk_widget_set_margin_top(changer->change, 5);
	}
	else
	{
		gtk_widget_set_hexpand(changer->label, FALSE);
		changer->change = gtk_scale_new(GTK_ORIENTATION_HORIZONTAL, adj);
		gtk_scale_set_digits(GTK_SCALE(changer->change), 0);
		gtk_widget_set_hexpand(changer->change, TRUE);
	}
}
