/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_set_default_params.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 21:49:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/04 21:49:54 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

void	gtk_set_default_params(GTK_DATA *gtk)
{
	gtk->img.info.key = 0;
	gtk->img.info.update_ocl = TRUE;
	gtk->img.rows = ROWS;
	gtk->img.cols = COLS;
	gtk->img.bpp = BYTES_PER_PIXEL;
	gtk->img.stride = COLS * BYTES_PER_PIXEL;
	gtk->img.stride += (4 - gtk->img.stride % 4) % 4;
	gtk->hints.min_width = COLS;
	gtk->hints.min_height = ROWS;
	gtk->hints.max_width = 1500;
	gtk->hints.max_height = 1000;
}
