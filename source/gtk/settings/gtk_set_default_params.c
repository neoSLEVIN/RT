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
	gtk->rt.info.key = 0;
	gtk->rt.info.update_ocl = TRUE;
	gtk->rt.rows = ROWS;
	gtk->rt.cols = COLS;
	gtk->rt.bpp = BYTES_PER_PIXEL;
	gtk->rt.stride = COLS * BYTES_PER_PIXEL;
	gtk->rt.stride += (4 - gtk->rt.stride % 4) % 4;
	gtk->hints.min_width = COLS;
	gtk->hints.min_height = ROWS;
	gtk->hints.max_width = 1500;
	gtk->hints.max_height = 1000;
}
