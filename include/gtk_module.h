/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_module.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/17 07:51:08 by cschoen          ###   ########.fr       */
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

// TODO dynamic value
# define STEP 0.5
# define UI_WIDTH 300

/*
** =============================================================================
** ================================ GTK entity =================================
** =========== Contains information about Widgets and their settings ===========
** =============================================================================
*/
typedef struct		s_gtk_data
{
	GtkWidget		*window;
	GtkWidget		*h_box;
	GtkWidget		*image_event_box;
	GtkImage		*image;
	GdkPixbuf		*pixbuf;
	guchar			*buffer;
	GtkWidget		*ui_v_box;
	GtkWidget		*fps_h_box;
	GtkWidget		*fps_label;
	GtkAdjustment	*fps_adj;
	GtkWidget		*fps_scale;
	GtkWidget		*y_axis;
	GtkWidget		*x_axis;
	GtkWidget		*button;
	guint			timeout_id;
}					t_gtk;

/*
** =============================================================================
** ============================= Main information ==============================
** ============= Send this entity to all signals, functions, etc. ==============
** ============= Contains info about Scene, OpenCL data, GTK data ==============
** =============================================================================
*/
typedef struct		s_rt_data
{
	t_info			*info;
	t_ocl			*ocl;
	SCENE			*scene;
	t_gtk			*gtk;
}					t_rt;

/*
** =============================================================================
** ================================= Settings ==================================
** =============================================================================
*/
void				gtk_set_main_window(t_gtk *gtk);
void				gtk_set_objects(t_gtk *gtk, t_rt *rt);
void				gtk_set_signals(t_rt *rt);
void				gtk_set_positions(t_gtk *gtk);

/*
** =============================================================================
** ================================== Signals ==================================
** =============================================================================
*/
int					draw_by_timeout(gpointer data);
gboolean			escape_window(GtkWidget *window, GdkEventKey *event,
									gpointer data);
gboolean			press_key_on_window(GtkWidget *window, GdkEventKey *event,
									gpointer data);
gboolean			release_key_on_window(GtkWidget *window, GdkEventKey *event,
									gpointer data);
gboolean			press_button_on_image_event_box(GtkWidget *event_box,
									GdkEventButton *event, gpointer data);
gboolean			release_button_on_image_event_box(GtkWidget *event_box,
									GdkEventButton *event, gpointer data);
gboolean			motion_button_on_image_event_box(GtkWidget *event_box,
									GdkEventMotion *event, gpointer data);
void				fps_scale_moved(GtkRange *range, gpointer data);
void				change_axis(GtkToggleButton *toggle_button, gpointer data);

/*
** =============================================================================
** ================================== Actions ==================================
** =============================================================================
*/

/*
** ================ Main action for run OpenCL and update image ================
*/
void				draw_image(t_rt *rt);
/*
** ============================ Factory for actions ============================
*/
void				make_action(t_rt *rt);
/*
** ================= Changing the state of flags and counters ==================
*/
void				increase_holders_cnt(int *count, _Bool *button, t_rt *rt);
void				decrease_holders_cnt(int *count, _Bool *button);
/*
** ==================== Update the marked (selected) shape =====================
*/
void				get_shape_id(t_rt *rt);
/*
** ========= Bindings for calling actions for camera and shape motion ==========
*/
void				move_camera_with_shape(t_rt *rt, guint key);
void				rotate_camera_with_shape(t_rt *rt, guint key);
void				rotate_camera_by_mouse_with_shape(t_rt *rt);
/*
** =============================== Camera motion ===============================
*/
void				move_camera(t_rt *rt, guint key);
void				rotate_camera(t_rt *rt, guint key);
void				rotate_camera_by_mouse(t_rt *rt, INT2 diff);
/*
** =============================== Shape motion ================================
*/
void				move_shape_by_camera_movement(t_rt *rt, guint key);
void				move_shape_by_camera_rotating(t_rt *rt, guint key);
void				move_shape_by_mouse(t_rt *rt, INT2 diff);

/*
** =============================================================================
** =================================== Utils ===================================
** =============================================================================
*/
void				init_info(t_info **info);
void				keys_to_false(t_info *info);
void				mouse_to_false(t_info *info);
void				new_scene(SCENE **scene);
void				new_gtk(t_rt *rt);
void				clear_rt(t_rt *rt);
void				clear_shape_marker(t_rt *rt);
void				clear_light_marker(t_rt *rt);
void				clear_lights(LIGHT **light);
void				clear_shapes(SHAPE **shape);

#endif
