/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_module.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 22:47:04 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/05 07:39:10 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef GTK_MODULE_H
#define GTK_MODULE_H

# include <gtk/gtk.h>
# include <glib.h>
# include <cairo.h>
# include <gdk-pixbuf/gdk-pixbuf.h>
# include "parser.h"
# include "ocl.h"

# define IMG_DATA struct s_image_data
# define GTK_DATA struct s_gtk_data

typedef struct	s_info
{
	guint		key;
	_Bool		update_ocl;
}				t_info;

struct			s_image_data
{
	GtkImage	*image;
	GdkPixbuf	*pixbuf;
	guchar		*buffer;
	t_scene		*scene;
	t_ocl		*ocl;
	t_info		info;
	int			rows;
	int			cols;
	int			bpp;
	int			stride;
};

struct			s_gtk_data
{
	IMG_DATA	img;
	GtkWidget	*window;
	GdkGeometry	hints;
	GtkWidget	*h_box;
	GtkWidget	*button;
};

/*
** ================================= Settings ==================================
*/
void			gtk_set_default_params(GTK_DATA *gtk);
void			gtk_set_main_window(GTK_DATA *gtk);
void			gtk_set_objects(GTK_DATA *gtk);
void			gtk_set_signals(GTK_DATA *gtk);
void			gtk_set_positions(GTK_DATA *gtk);
/*
** ================================== Actions ==================================
*/
void			draw_image(GtkWidget *button, gpointer data);
/*
** =================================== Utils ===================================
*/
GTK_DATA		*new_gtk(t_scene *scene, t_ocl *ocl);
void			gtk_clear(GTK_DATA **gtk);
t_scene			*new_scene(void);
void			clear_lights(LIGHT_LIST **list_light);
void			clear_shapes(SHAPE_LIST **list_shape);

#endif