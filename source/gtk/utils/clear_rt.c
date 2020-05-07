/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_rt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 07:13:52 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/07 04:45:07 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

void	clear_rt(t_rt *rt)
{
	if (!rt)
		return ;
	ft_memdel((void*)&rt->ocl);			//TODO clear_ocl(t_ocl **ocl);
	ft_memdel((void*)&rt->scene);		//TODO clear_scene(t_scene **scene);
	g_slice_free(t_gtk, rt->gtk);	//TODO clear_gtk(t_gtk **gtk);
}
