/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_set_spin_button.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 06:09:55 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:29:57 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

void	gtk_set_spin_button_for_float(GtkWidget **spin, cl_float value)
{
	GtkAdjustment	*adj;

	adj = gtk_adjustment_new(value, -MAX_FLOAT, MAX_FLOAT, 1.0, 10.0, 0);
	*spin = gtk_spin_button_new(adj, 1.0, 3);
	gtk_entry_set_width_chars(GTK_ENTRY(*spin), 7);
	gtk_spin_button_set_numeric(GTK_SPIN_BUTTON(*spin), TRUE);
	gtk_widget_set_margin_bottom(*spin, 5);
}

void	gtk_set_spin_button_for_radius(GtkWidget **spin, cl_float value)
{
	GtkAdjustment	*adj;

	adj = gtk_adjustment_new(value, 0.1f, MAX_FLOAT, 0.5, 10.0, 0);
	*spin = gtk_spin_button_new(adj, 0.5, 3);
	gtk_entry_set_width_chars(GTK_ENTRY(*spin), 6);
	gtk_spin_button_set_numeric(GTK_SPIN_BUTTON(*spin), TRUE);
	gtk_widget_set_margin_bottom(*spin, 5);
}

void	gtk_set_spin_button_for_angle(GtkWidget **spin, cl_float value)
{
	GtkAdjustment	*adj;

	adj = gtk_adjustment_new(value, 1.0f, 89.0f, 0.1, 10.0, 0);
	*spin = gtk_spin_button_new(adj, 0.1, 1);
	gtk_entry_set_width_chars(GTK_ENTRY(*spin), 6);
	gtk_spin_button_set_numeric(GTK_SPIN_BUTTON(*spin), TRUE);
	gtk_widget_set_margin_bottom(*spin, 5);
}

void	gtk_set_spin_button_for_intensity(GtkWidget **spin, cl_float value)
{
	GtkAdjustment	*adj;

	adj = gtk_adjustment_new(value, 0.01, 1.0, 0.005, 0.1, 0);
	*spin = gtk_spin_button_new(adj, 0.1, 3);
	gtk_entry_set_width_chars(GTK_ENTRY(*spin), 4);
	gtk_spin_button_set_numeric(GTK_SPIN_BUTTON(*spin), TRUE);
	gtk_widget_set_margin_bottom(*spin, 5);
}
