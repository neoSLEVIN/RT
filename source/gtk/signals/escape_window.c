/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 19:55:26 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/09 19:55:26 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

gboolean	escape_window(GtkWidget *window, GdkEventKey *event, gpointer data)
{
	if (event->keyval == GDK_KEY_Escape)
	{
		gtk_main_quit();
		return (TRUE);
	}
	return (FALSE);
}
