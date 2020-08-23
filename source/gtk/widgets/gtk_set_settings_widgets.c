/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_set_settings_widgets.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 16:14:53 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/24 16:14:53 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

static void	gtk_set_filters_list(GtkComboBoxText *filter_combo)
{
	gtk_combo_box_text_append_text(filter_combo, "NO FILTER");
	gtk_combo_box_text_append_text(filter_combo, "SEPIA");
	gtk_combo_box_text_append_text(filter_combo, "NEGATIVE");
	gtk_combo_box_text_append_text(filter_combo, "NOISE");
	gtk_combo_box_text_append_text(filter_combo, "SHADES OF GRAY");
	gtk_combo_box_text_append_text(filter_combo, "BLUR");
	gtk_combo_box_text_append_text(filter_combo, "EMBOSS");
	gtk_combo_box_text_append_text(filter_combo, "SHARPEN");
}

void		gtk_set_settings_widgets(t_gtk_settings *settings, t_rt *rt)
{
	GtkAdjustment	*fps_adj;

	settings->expander = gtk_expander_new_with_mnemonic("S_ettings");
	settings->grid = gtk_grid_new();
	settings->fps_label = gtk_label_new("FPS:");
	gtk_widget_set_hexpand(settings->fps_label, FALSE);
	fps_adj = gtk_adjustment_new(rt->scene->fps, 0.5, 80.0, 0.5,1.0, 0);
	settings->fps_scale = gtk_scale_new(GTK_ORIENTATION_HORIZONTAL, fps_adj);
	gtk_scale_set_digits(GTK_SCALE(settings->fps_scale), 1);
	gtk_widget_set_hexpand(settings->fps_scale, TRUE);
	settings->y_axis = gtk_check_button_new_with_label("Invert Y-axis");
	gtk_widget_set_halign(settings->y_axis, GTK_ALIGN_CENTER);
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(settings->y_axis), FALSE);
	settings->separator = gtk_separator_new(GTK_ORIENTATION_VERTICAL);
	gtk_widget_set_valign(settings->separator, GTK_ALIGN_FILL);
	gtk_widget_set_halign(settings->separator, GTK_ALIGN_CENTER);
	settings->x_axis = gtk_check_button_new_with_label("Invert X-axis");
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(settings->x_axis), FALSE);
	settings->filter_label = gtk_label_new("Filter:");
	gtk_widget_set_margin_end(settings->filter_label, 5);
	settings->filter_combo = gtk_combo_box_text_new();
	gtk_set_filters_list(GTK_COMBO_BOX_TEXT(settings->filter_combo));
	gtk_combo_box_set_active(GTK_COMBO_BOX(settings->filter_combo),
		rt->scene->filter);
}
