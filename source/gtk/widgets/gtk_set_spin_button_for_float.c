/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_set_spin_button_for_float.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 06:09:55 by cschoen           #+#    #+#             */
/*   Updated: 2020/06/01 20:06:00 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

void	gtk_set_spin_button_for_percent(GtkWidget **spin, cl_float value)
{
	GtkAdjustment	*adj;

	//TODO change range
	adj = gtk_adjustment_new(value, 0.0, 100.0, 0.005, 10.0, 0);
	*spin = gtk_spin_button_new(adj, 0.1, 3);
	gtk_entry_set_width_chars(GTK_ENTRY(*spin), 4);
	gtk_spin_button_set_numeric(GTK_SPIN_BUTTON(*spin), TRUE);
	gtk_widget_set_margin_bottom(*spin, 5);
/*	g_signal_connect(*spin, "scroll-event",
					G_CALLBACK(spin_button_scroll_locker), NULL);*/
}

void	gtk_set_spin_button_for_one(GtkWidget **spin, cl_float value)
{
	GtkAdjustment	*adj;

	adj = gtk_adjustment_new(value, 0.0, 1.0, 0.005, 0.1, 0);
	*spin = gtk_spin_button_new(adj, 0.1, 3);
	gtk_entry_set_width_chars(GTK_ENTRY(*spin), 4);
	gtk_spin_button_set_numeric(GTK_SPIN_BUTTON(*spin), TRUE);
	gtk_widget_set_margin_bottom(*spin, 5);
}


void	gtk_set_spin_button_for_float(GtkWidget **spin, cl_float value)
{
	GtkAdjustment	*adj;

	adj = gtk_adjustment_new(value, -MAX_FLOAT, MAX_FLOAT, 1.0, 10.0, 0);
	*spin = gtk_spin_button_new(adj, 1.0, 3);
	gtk_entry_set_width_chars(GTK_ENTRY(*spin), 7);
	gtk_spin_button_set_numeric(GTK_SPIN_BUTTON(*spin), TRUE);
	gtk_widget_set_margin_bottom(*spin, 5);
/*	g_signal_connect(*spin, "scroll-event",
		G_CALLBACK(spin_button_scroll_locker), NULL);*/
}

void	gtk_set_spin_button_for_radius(GtkWidget **spin, cl_float value)
{
	GtkAdjustment	*adj;

	adj = gtk_adjustment_new(value, 0.1f, MAX_FLOAT, 1.0, 10.0, 0);
	*spin = gtk_spin_button_new(adj, 1.0, 3);
	gtk_entry_set_width_chars(GTK_ENTRY(*spin), 7);
	gtk_spin_button_set_numeric(GTK_SPIN_BUTTON(*spin), TRUE);
	gtk_widget_set_margin_bottom(*spin, 5);
}
