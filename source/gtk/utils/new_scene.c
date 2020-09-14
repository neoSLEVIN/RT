/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/09 16:39:25 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

void			new_scene(SCENE **scene, GtkWidget **win)
{
	char	*filename;

	filename = NULL;
	if (!choose_file_name(GTK_WINDOW(*win), &filename, SCENE_PATH))
	{
		ft_printf("Close \"Open File\" tab\n");
		exit(0);
	}
	else if (!filename)
		ft_error("Bad initiation of file");
	*scene = parse_scene(filename);
	(*scene)->filename = filename;
}
