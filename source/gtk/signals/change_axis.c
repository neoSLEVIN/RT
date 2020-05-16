/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_axis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/16 03:58:26 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/16 03:58:26 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

void	change_axis(GtkToggleButton *toggle_button, gpointer data)
{
	cl_int	*axis;

	axis = (cl_int*)data;
	*axis *= -1;
}
