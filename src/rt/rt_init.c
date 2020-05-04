/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 21:02:52 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/04 22:13:20 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	rt_clear(t_rt *rt)
{
	ft_memdel((void*)&rt->ocl);		//TODO clear_ocl(t_ocl **ocl);
	ft_memdel((void*)&rt->scene);	//TODO clear_scene(t_scene **scene);
	g_slice_free(GTK_DATA, rt->gtk);
}

void	rt_init(t_rt *rt)
{
	rt->ocl = new_ocl();
	rt->scene = new_scene();
	rt->gtk = new_gtk(rt->scene, rt->ocl);
}
