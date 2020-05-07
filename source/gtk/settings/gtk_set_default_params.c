/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_set_default_params.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 21:49:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/07 04:44:58 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

void	gtk_set_default_params(t_gtk *gtk)
{
	gtk->hints.min_width = COLS;
	gtk->hints.min_height = ROWS;
	gtk->hints.max_width = 1500;
	gtk->hints.max_height = 1000;
}
