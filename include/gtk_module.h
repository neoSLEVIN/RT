/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_module.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 22:47:04 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/06 20:26:45 by cschoen          ###   ########lyon.fr   */
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
	_Bool		update_ocl;
	guint		key;
	double		mouse_x;
	double		mouse_y;
}				t_info;

/*
** =============================================================================
** ============================= Main information ==============================
** ============= Send this entity to all signals, functions, etc. ==============
** ========== Contains info about Scene, OpenCL data, Main GTK Image ===========
** =============================================================================
*/
# define RT_DATA struct s_rt_data
struct			s_rt_data
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

/*
** =============================================================================
** ============================== Main GTK entity ==============================
** ==== Contains information about Widgets, their settings and data for RT =====
** =============================================================================
*/
# define GTK_DATA struct s_gtk_data
struct			s_gtk_data
{
	RT_DATA		rt;
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
void			clear_lights(LIGHT **light);
void			clear_shapes(SHAPE **shape);

#endif
