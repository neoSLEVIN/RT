/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_set_settings_widgets.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 16:14:53 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:29:46 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

void	gtk_set_settings_widgets(t_gtk_settings *settings, t_rt *rt)
{
	settings->expander = gtk_expander_new_with_mnemonic("S_ettings");
	settings->v_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	settings->grid = gtk_grid_new();
	settings->anti_aliasing = gtk_check_button_new_with_label("Anti-aliasing");
	gtk_set_setting_filter_widgets(settings, rt);
}
