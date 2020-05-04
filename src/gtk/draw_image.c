/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 16:35:03 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/05 00:50:30 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

void	test_ocl(t_ocl *ocl)
{
	for (int i = 0; i < ocl->mem_length; ++i)
		ft_printf("%{}d\t", (i % 2 ? FT_BLUE : FT_PURPLE), (int)ocl->mem[0][i]);
	ft_putendl("\n");
}

void	draw_image(GtkWidget *button, gpointer data)
{
	IMG_DATA	*img;
	int			pixel;
	int			row;
	int			col;

	img = (IMG_DATA*)data;
	if (img->info.update_ocl)
		set_params_cl(img->ocl);
	img->info.update_ocl = FALSE;
	run_cl(img->ocl);
	//test_ocl(img->ocl);
	row = -1;
	while (++row < img->rows)
	{
		col = -1;
		while (++col < img->cols)
		{
			pixel = row * img->stride + col * img->bpp;
			img->buffer[pixel] = (((int)img->ocl->mem[0][row * col]) >> 16) & 0xFF;
			img->buffer[pixel + 1] = (((int)img->ocl->mem[0][row * col]) >> 8) & 0xFF;
			img->buffer[pixel + 2] = ((int)img->ocl->mem[0][row * col]) & 0xFF;
		}
	}
	gtk_image_set_from_pixbuf(GTK_IMAGE(img->image), img->pixbuf);
}
