/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_module.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 22:47:04 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/07 05:10:48 by cschoen          ###   ########lyon.fr   */
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

/*
** ============= Additional info about keys, flags, etc for UI/UX ==============
*/
typedef struct	s_info
{
	guint		key;
	double		mouse_x;
	double		mouse_y;
}				t_info;

/*
** =============================================================================
** ================================ GTK entity =================================
** =========== Contains information about Widgets and their settings ===========
** =============================================================================
*/
typedef struct	s_gtk_data
{
	GtkWidget	*window;
	GdkGeometry	hints;
	GtkWidget	*h_box;
	GtkImage	*image;
	GdkPixbuf	*pixbuf;
	guchar		*buffer;
	GtkWidget	*button;
}				t_gtk;

/*
** =============================================================================
** ============================= Main information ==============================
** ============= Send this entity to all signals, functions, etc. ==============
** ============= Contains info about Scene, OpenCL data, GTK data ==============
** =============================================================================
*/
typedef struct	s_rt_data
{
	t_scene		*scene;
	t_ocl		*ocl;
	t_info		info;
	t_gtk		*gtk;
}				t_rt;

/*
** ================================= Settings ==================================
*/
void			gtk_set_default_params(t_gtk *gtk);
void			gtk_set_main_window(t_gtk *gtk);
void			gtk_set_objects(t_gtk *gtk, cl_char4 *buffer);
void			gtk_set_signals(t_rt *rt);
void			gtk_set_positions(t_gtk *gtk);
/*
** ================================== Actions ==================================
*/
void			draw_image(t_rt *rt);
void			update_cam(t_rt *rt);
/*
** =================================== Utils ===================================
*/
t_scene			*new_scene(void);
void			new_gtk(t_rt *rt);
void			init_info(t_info *info);
void			clear_rt(t_rt *rt);
void			clear_lights(LIGHT **light);
void			clear_shapes(SHAPE **shape);

#endif
