/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 16:35:03 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/06 06:31:48 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

void	test_ocl(t_ocl *ocl)
{
	for (int i = 0; i < ocl->work_size; ++i)
		if (ocl->dto.buffer[i].x != 0 || ocl->dto.buffer[i].y != 0 || ocl->dto.buffer[i].z != 0)
			ft_printf("%{}.f %{}.f %{}.f\t",
				FT_BLUE, ocl->dto.buffer[i].x,
				FT_PURPLE, ocl->dto.buffer[i].y,
				FT_YELLOW, ocl->dto.buffer[i].z);
	ft_putendl("\n");
}

static void	put_color_to_pixel(FLT3 color, guchar *pixel)
{
	pixel[0] = (guchar)color.x;
	pixel[1] = (guchar)color.y;
	pixel[2] = (guchar)color.z;
}

void		draw_image(GtkWidget *button, gpointer data)
{
	IMG_DATA	*img;
	int			row;
	int			col;

	img = (IMG_DATA*)data;
	if (img->info.update_ocl)
		set_params_cl(img->ocl, img->scene);
	img->info.update_ocl = FALSE;
	run_cl(img->ocl);
	row = -1;
	while (++row < img->rows)
	{
		col = -1;
		while (++col < img->cols)
			put_color_to_pixel(img->ocl->dto.buffer[row * img->cols + col],
					&img->buffer[row * img->stride + col * img->bpp]);
	}
//	test_ocl(img->ocl);
	gtk_image_set_from_pixbuf(GTK_IMAGE(img->image), img->pixbuf);
}
