/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/30 03:51:29 by cschoen           #+#    #+#             */
/*   Updated: 2020/04/01 03:49:43 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <gtk/gtk.h>
# include "ocl.h"

typedef struct			s_img
{
	void				*img_ptr;
	char				*data;
	int					bpp;
	int					size_line;
	int					endian;
	int					width;
	int					height;
}						t_img;

typedef struct			s_mlx
{
	void				*mlx_ptr;
	void				*win_ptr;
	t_img				*rgb;
}						t_mlx;

typedef struct			s_rt
{
	t_ocl				ocl;
	t_mlx				mlx;
	double				mouse_x;
	double				mouse_y;
}						t_rt;

#endif
