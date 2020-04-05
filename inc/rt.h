/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/30 03:51:29 by cschoen           #+#    #+#             */
/*   Updated: 2020/04/05 00:05:46 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <gtk/gtk.h>
# include "ocl.h"
# include "utils.h"
# include "parser.h"

# define TEMP_SRC_JSON "C:\\Users\\slevi\\CLionProjects\\RT\\scene\\scene.json"

typedef struct			s_rt
{
	t_ocl				ocl;
	double				mouse_x;
	double				mouse_y;
}						t_rt;

#endif
