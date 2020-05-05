/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_clear.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 07:13:52 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/05 07:13:52 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

void	gtk_clear(GTK_DATA **gtk)
{
	if (!gtk || !*gtk)
		return ;
	ft_memdel((void*)&(*gtk)->img.ocl);		//TODO clear_ocl(t_ocl **ocl);
	ft_memdel((void*)&(*gtk)->img.scene);	//TODO clear_scene(t_scene **scene);
	g_slice_free(GTK_DATA, *gtk);
}
