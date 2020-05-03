/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/30 03:51:29 by cschoen           #+#    #+#             */
/*   Updated: 2020/04/12 21:52:54 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include "utils.h"
# include "gtk_module.h"
# include "parser.h"
# include "ocl.h"

typedef struct			s_rt
{
	t_ocl				ocl;
	double				mouse_x;
	double				mouse_y;
}						t_rt;

#endif
