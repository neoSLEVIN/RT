/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_set_scale_widgets.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:29:39 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:29:39 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

t_spinner	gtk_set_spinner_float(const char *label, FLT2 range, cl_float value,
								cl_float step)
{
	t_spinner		spinner;
	GtkAdjustment	*adj;

	spinner.label = gtk_label_new(label);
	gtk_widget_set_margin_start(spinner.label, 5);
	gtk_widget_set_margin_end(spinner.label, 5);
	gtk_widget_set_margin_top(spinner.label, 5);
	adj = gtk_adjustment_new(value, range.x, range.y, step, range.y / 10, 0);
	spinner.spin = gtk_spin_button_new(adj, step, 3);
	gtk_entry_set_width_chars(GTK_ENTRY(spinner.spin), 6);
	gtk_spin_button_set_numeric(GTK_SPIN_BUTTON(spinner.spin), TRUE);
	gtk_widget_set_margin_top(spinner.spin, 5);
	return (spinner);
}

void		gtk_set_spinner(t_spinner *spinner, INT2 range, int value,
						const char *label)
{
	GtkAdjustment	*adj;

	spinner->label = gtk_label_new(label);
	gtk_widget_set_margin_start(spinner->label, 5);
	gtk_widget_set_margin_end(spinner->label, 5);
	gtk_widget_set_margin_top(spinner->label, 5);
	adj = gtk_adjustment_new(value, range.x, range.y, 1, range.y / 10, 0);
	spinner->spin = gtk_spin_button_new(adj, 1, 0);
	gtk_entry_set_width_chars(GTK_ENTRY(spinner->spin), 5);
	gtk_spin_button_set_numeric(GTK_SPIN_BUTTON(spinner->spin), TRUE);
	gtk_widget_set_margin_top(spinner->spin, 5);
}

void		gtk_set_scale(t_scale *scale, INT2 range, int value,
					const char *label)
{
	GtkAdjustment	*adj;

	scale->label = gtk_label_new(label);
	gtk_widget_set_hexpand(scale->label, FALSE);
	adj = gtk_adjustment_new(value, range.x, range.y, 1, range.y / 3, 0);
	scale->scale = gtk_scale_new(GTK_ORIENTATION_HORIZONTAL, adj);
	gtk_scale_set_digits(GTK_SCALE(scale->scale), 0);
	gtk_widget_set_hexpand(scale->scale, TRUE);
}

t_scale		gtk_get_float_scale(const char *label, FLT2 range, cl_float value,
							cl_float step)
{
	t_scale			scale;
	GtkAdjustment	*adj;

	scale.label = gtk_label_new(label);
	gtk_widget_set_hexpand(scale.label, FALSE);
	gtk_widget_set_margin_start(scale.label, 5);
	gtk_widget_set_margin_top(scale.label, 5);
	adj = gtk_adjustment_new(value, range.x, range.y, step, range.y / 10, 0);
	scale.scale = gtk_scale_new(GTK_ORIENTATION_HORIZONTAL, adj);
	gtk_scale_set_digits(GTK_SCALE(scale.scale), 3);
	gtk_widget_set_hexpand(scale.scale, TRUE);
	gtk_widget_set_margin_top(scale.scale, 5);
	return (scale);
}
