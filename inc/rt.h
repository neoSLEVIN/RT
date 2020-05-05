/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/30 03:51:29 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/04 21:41:10 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include "gtk_module.h"

typedef struct	s_rt
{
	t_scene		*scene;
	t_ocl		*ocl;
	GTK_DATA	*gtk;
}				t_rt;

void			rt_init(t_rt *rt);
void			rt_clear(t_rt *rt);

void			rt_lights_del(t_list_light **list_light);
void			rt_shapes_del(t_list_shape **list_shape);

#endif
