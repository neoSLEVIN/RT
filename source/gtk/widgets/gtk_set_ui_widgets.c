/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_set_ui_widgets.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 05:58:19 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/29 05:58:19 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

void	gtk_set_ui_widgets(t_ui *ui)
{
	ui->scrolled_window = gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_min_content_height(GTK_SCROLLED_WINDOW(
		ui->scrolled_window), ROWS);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(ui->scrolled_window),
		GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	ui->grid = gtk_grid_new();
	gtk_widget_set_margin_start(GTK_WIDGET(ui->grid), 10);
	gtk_widget_set_margin_end(GTK_WIDGET(ui->grid), 10);
	gtk_widget_set_margin_bottom(GTK_WIDGET(ui->grid), 10);
}
