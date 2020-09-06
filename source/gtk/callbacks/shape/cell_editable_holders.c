/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cell_editable_holders.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:23:29 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:23:29 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

void	cell_editable_holders(GtkCellRenderer *renderer,
							GtkCellEditable *editable, gchar *row_index,
							gpointer data)
{
	(void)renderer;
	(void)row_index;
	(void)data;
	if (GTK_IS_COMBO_BOX(editable))
		gtk_combo_box_set_wrap_width(GTK_COMBO_BOX(editable), 10);
	else if (GTK_IS_SPIN_BUTTON(editable))
		gtk_spin_button_set_numeric(GTK_SPIN_BUTTON(editable), TRUE);
}
