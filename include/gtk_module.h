/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_module.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/06/01 22:27:50 by cschoen          ###   ########.fr       */
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
# define UI_WIDTH 400
# define GTK_SELECT GtkTreeSelection

/*
** =================== Entity for spin button and his label ====================
*/
typedef struct		s_spinner
{
	GtkWidget		*spin;
	GtkWidget		*label;
}					t_spinner;

/*
** =============================================================================
** ============================ Main Image entity ==============================
** ========== Contains information about pixels and widget-containers ==========
** =============================================================================
*/
typedef struct		s_gtk_image
{
	GtkWidget		*image_event_box;
	GtkImage		*image;
	GdkPixbuf		*pixbuf;
	guchar			*buffer;
}					t_gtk_image;

/*
** =============================================================================
** =============== Tab for changing transform properties of shape ==============
** =============================================================================
*/
typedef struct		s_transform_tab
{
	GtkWidget		*label;
	GtkWidget		*grid;
	GtkWidget		*label_pos;
	t_spinner		x;
	t_spinner		y;
	t_spinner		z;
}					t_transform_tab;

/*
** =============================================================================
** =============== Tab for changing material properties of shape ===============
** =============================================================================
*/
typedef struct		s_material_tab
{
	GtkWidget		*label;
	GtkWidget		*grid;
	t_spinner		specular;
	t_spinner		reflective;
	t_spinner		transparency;
}					t_material_tab;

/*
** =============================================================================
** =============== Tab for changing material properties of shape ===============
** =============================================================================
*/
typedef struct		s_section_tab
{
	GtkWidget		*label;
	GtkWidget		*grid;
	GtkWidget		*on_x;
	GtkWidget		*on_y;
	GtkWidget		*on_z;
}					t_section_tab;

/*
** =============================================================================
** ==================== Entity for changing shape properties ===================
** ============= Contains all entities for tabs in notebook widget =============
** =============================================================================
*/
typedef struct		s_gtk_shape
{
	GtkWidget		*expander;
	GtkWidget		*frame;
	GtkWidget		*notebook;
	t_transform_tab	transform;
	t_material_tab	material;
	t_section_tab	section;
	SHAPE			*shape;
}					t_gtk_shape;

/*
** =============================================================================
** ========================= Entity for list of shapes =========================
** =============================================================================
*/
typedef struct		s_gtk_shapes
{
	GtkWidget		*expander;
	GtkWidget		*scrolled_window;
	GtkWidget		*tree;
	GtkTreeStore	*store;
	GtkTreeModel	*model;
	GtkTreeIter		iter;
	GTK_SELECT		*select;
	GtkCellRenderer	*text_renderer;
	GtkCellRenderer	*toggle_renderer;
}					t_gtk_shapes;
/*
** ========================== Columns for shapes tree ==========================
*/
typedef enum		e_shapes_column
{
	S_NAME_COL,
	S_TYPE_COL,
	S_MARKER_COL,
	S_POINTER_COL,
	S_COL_CNT
}					t_shapes_column;

/*
** =============================================================================
** ============================ Entity for textures ============================
** =============================================================================
*/
typedef struct		s_gtk_textures
{
	GtkWidget		*expander;
	GtkWidget		*scrolled_window;
	GtkWidget		*tree;
	GtkTreeStore	*store;
	GtkTreeIter		iter;
	GtkCellRenderer	*renderer;
}					t_gtk_textures;

/*
** =============================================================================
** ============================ Entity for settings ============================
** =============================================================================
*/
typedef struct		s_gtk_settings
{
	GtkWidget		*expander;
	GtkWidget		*grid;
	GtkWidget		*fps_label;
	GtkWidget		*fps_scale;
	GtkWidget		*y_axis;
	GtkWidget		*separator;
	GtkWidget		*x_axis;
}					t_gtk_settings;

/*
** =============================================================================
** ============================== Main UI entity ===============================
** ======================= Contains all side UI entities =======================
** =============================================================================
*/
typedef struct		s_ui
{
	GtkWidget		*scrolled_window;
	GtkWidget		*grid;
	t_gtk_shape		*shape;
	t_gtk_shapes	shapes;
	t_gtk_textures	texture;
	t_gtk_settings	settings;
}					t_ui;

/*
** =============================================================================
** ============================= Main GTK entity ===============================
** ========== Contains information about Widgets and their properties ==========
** =============================================================================
*/
typedef struct		s_gtk_data
{
	GtkWidget		*window;
	GtkWidget		*window_h_box;
	t_gtk_image		img;
	t_ui			ui;
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
void				gtk_set_widgets(t_gtk *gtk, t_rt *rt);
void				gtk_set_signals(t_rt *rt);
void				gtk_set_positions(t_gtk *gtk);

/*
** =============================================================================
** ================================== Widgets ==================================
** =============================================================================
*/
void				gtk_set_image_with_dependencies(t_gtk *gtk,
									cl_char4 *dto_buffer);
void				gtk_set_ui_widgets(t_ui *ui);
void				gtk_set_shape_widgets(t_gtk_shape **gtk_shape,
									SHAPE *scene_shape);
void				gtk_set_shapes_tree(t_gtk_shapes *shapes, t_rt *rt);
void				gtk_set_textures_tree(t_gtk_textures *textures, t_rt *rt);
void				gtk_set_settings_widgets(t_gtk_settings *settings,
									t_rt *rt);
void				gtk_set_spin_button_for_float(GtkWidget **spin,
									cl_float value);
void				gtk_set_spin_button_for_percent(GtkWidget **spin,
									cl_float value);

/*
** =============================================================================
** ================================= Positions =================================
** =============================================================================
*/
void				gtk_set_settings_positions(t_gtk_settings *settings);
void				gtk_set_shapes_positions(t_gtk_shapes *shapes);
void				gtk_set_shape_positions(t_gtk_shape *shape);

/*
** =============================================================================
** ================================== Signals ==================================
** =============================================================================
*/
void				gtk_set_motions_signals(GtkWidget *window,
									GtkWidget *image_event_box, t_rt *rt);
void				gtk_set_shape_signals(t_rt *rt);
void				gtk_set_shapes_signals(t_rt *rt);
void				gtk_set_ui_settings_signals(t_gtk_settings *settings,
									t_rt *rt);

/*
** =============================================================================
** ================================= Callbacks =================================
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
gboolean			scroll_on_image_event_box(GtkWidget *event_box,
									GdkEvent *event, gpointer data);
gboolean			spin_button_scroll_locker(GtkWidget *widget,
									GdkEvent *event, gpointer data);
void				spin_button_shape_position_changer(GtkSpinButton *button,
									gpointer data);
void				shapes_tree_selection_changer(GtkTreeSelection *selection,
									gpointer data);
void				shapes_tree_double_click(GtkTreeView *tree,
									GtkTreePath *path, GtkTreeViewColumn *col,
									gpointer data);
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
** ================= Update the marked (selected) shape/light ==================
*/
void				get_shape_id(t_rt *rt);
void				update_shape_marker(t_rt *rt, SHAPE *shape);
void				clear_shape_marker(t_rt *rt);
void				clear_light_marker(t_rt *rt);
void				update_shapes_flags(_Bool *update_shapes,
										_Bool *update_property);
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
void				rotate_shape(t_rt *rt, guint key);
/*
** ======================== Change the shape parameters ========================
*/
void				change_shape_param(t_rt *rt);
/*
** ============================== Update widgets ===============================
*/
gboolean			update_shape_widget(gpointer data);

/*
** =============================================================================
** =================================== Utils ===================================
** =============================================================================
*/
void				init_info(t_info **info);
void				keys_to_false(t_info *info);
void				mouse_to_false(t_info *info);
void				shape_to_false(t_info *info);
void				shape_to_true(t_info *info);
void				new_scene(SCENE **scene);
void				new_gtk(t_rt *rt);
void				clear_rt(t_rt *rt);
void				clear_lights(LIGHT **light);
void				clear_shapes(SHAPE **shape);
char				*get_shape_type_name(SHAPE_TYPE type);

#endif
