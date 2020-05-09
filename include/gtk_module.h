/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_module.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/09 20:16:52 by cschoen          ###   ########.fr       */
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
	_Bool		update;
	int			holders_cnt;
	_Bool		w_key;
	_Bool		s_key;
	_Bool		a_key;
	_Bool		d_key;
	_Bool		q_key;
	_Bool		e_key;
	double		mouse_x;
	double		mouse_y;
	guint		key;
	LIGHT		*l_marker;
	SHAPE		*s_marker;
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
	GtkWidget	*image_event_box;
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
	SCENE		*scene;
	t_ocl		*ocl;
	t_info		*info;
	t_gtk		*gtk;
}				t_rt;

/*
** ================================= Settings ==================================
*/
void			gtk_set_default_params(t_gtk *gtk);
void			gtk_set_main_window(t_gtk *gtk);
void			gtk_set_objects(t_gtk *gtk, cl_char4 *dto_buffer);
void			gtk_set_signals(t_rt *rt);
void			gtk_set_positions(t_gtk *gtk);
/*
** ================================== Signals ==================================
*/
gboolean		escape_window(GtkWidget *window, GdkEventKey *event,
								gpointer data);
gboolean		press_key_on_window(GtkWidget *window, GdkEventKey *event,
									gpointer data);
gboolean		release_key_on_window(GtkWidget *window, GdkEventKey *event,
									gpointer data);
gboolean		press_button_on_image_event_box(GtkWidget *event_box,
									GdkEventButton *event, gpointer data);
gboolean		release_button_on_image_event_box(GtkWidget *event_box,
									GdkEventButton *event, gpointer data);
/*
** ================================== Actions ==================================
*/
void			increase_holders_cnt(int *count, _Bool *button);
void			decrease_holders_cnt(int *count, _Bool *button);
void			draw_image(t_rt *rt);
void			move_cam(t_rt *rt, guint key);
void			rotate_cam(t_rt *rt, guint key);
void			update_cam(t_rt *rt);
/*
** =================================== Utils ===================================
*/
void			init_info(t_info **info);
void			new_scene(SCENE **scene);
void			new_gtk(t_rt *rt);
void			clear_rt(t_rt *rt);
void			clear_lights(LIGHT **light);
void			clear_shapes(SHAPE **shape);

#endif
