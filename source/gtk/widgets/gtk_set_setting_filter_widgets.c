/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_set_setting_filter_widgets.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:29:42 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:29:43 by cschoen          ###   ########.fr       */
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

void		gtk_set_setting_filter_widgets(t_gtk_settings *settings, t_rt *rt)
{
	settings->filter_label = gtk_label_new("Filter:");
	gtk_widget_set_margin_end(settings->filter_label, 5);
	gtk_widget_set_margin_top(settings->filter_label, 5);
	settings->filter_combo = gtk_combo_box_text_new();
	gtk_widget_set_margin_top(settings->filter_combo, 5);
	gtk_set_filters_list(GTK_COMBO_BOX_TEXT(settings->filter_combo));
	gtk_combo_box_set_active(GTK_COMBO_BOX(settings->filter_combo),
							rt->scene->filter);
	settings->v_filter_params = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	settings->grid_blur = gtk_grid_new();
	settings->grid_sepia = gtk_grid_new();
	settings->grid_noise = gtk_grid_new();
	gtk_set_spinner(&settings->blur, (INT2){1, 255},
				rt->scene->filter_params.x, "Blur:");
	gtk_set_spinner(&settings->sepia, (INT2){1, 255},
				rt->scene->filter_params.y, "Sepia:");
	gtk_set_spinner(&settings->noise, (INT2){1, 255},
				rt->scene->filter_params.z, "Noise:");
}
