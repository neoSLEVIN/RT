/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 16:35:03 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/05 05:51:54 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

void	test_ocl(t_ocl *ocl)
{
	for (int i = 0; i < ocl->mem_length; ++i)
		ft_printf("%{}d\t", (i % 2 ? FT_BLUE : FT_PURPLE), (int)ocl->mem[0][i]);
	ft_putendl("\n");
}

static void	put_color_to_pixel(int color, guchar *pixel)
{
	pixel[0] = (color & 0xFF0000) >> 16;
	pixel[1] = (color & 0xFF00) >> 8;
	pixel[2] = color & 0xFF;
}

void	draw_image(GtkWidget *button, gpointer data)
{
	IMG_DATA	*img;
	int			row;
	int			col;

	img = (IMG_DATA*)data;
	if (img->info.update_ocl)
		set_params_cl(img->ocl);
	img->info.update_ocl = FALSE;
	run_cl(img->ocl);
	row = -1;
	while (++row < img->rows)
	{
		col = -1;
		while (++col < img->cols)
			put_color_to_pixel((int)img->ocl->mem[0][row * img->cols + col],
					&img->buffer[row * img->stride + col * img->bpp]);
	}
	gtk_image_set_from_pixbuf(GTK_IMAGE(img->image), img->pixbuf);
}
