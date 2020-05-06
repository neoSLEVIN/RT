/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 16:35:03 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/06 23:50:21 by cschoen          ###   ########lyon.fr   */
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
	RT_DATA	*rt;
	int		row;
	int		col;

	rt = (RT_DATA*)data;
	if (rt->info.update_ocl)
		setting_cl(rt->ocl, rt->scene);
	rt->info.update_ocl = FALSE;
	run_cl(rt->ocl);
	row = -1;
	while (++row < rt->rows)
	{
		col = -1;
		while (++col < rt->cols)
			put_color_to_pixel(rt->ocl->dto.buffer[row * rt->cols + col],
				&rt->buffer[row * rt->stride + col * rt->bpp]);
	}
//	test_ocl(rt->ocl);
	gtk_image_set_from_pixbuf(GTK_IMAGE(rt->image), rt->pixbuf);
	rt->scene->cam.transform.position.z += 0.5;
	translate_cam(&rt->ocl->dto.cam, &rt->scene->cam);
	int err = clSetKernelArg(rt->ocl->kernel, 4, sizeof(DTO_CAM), &(rt->ocl->dto.cam));
	check_error_cl(err,"clSetKernelArg", "cam");
}
