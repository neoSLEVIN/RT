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
** ==================== Enum of Shape notebook widget tabs =====================
** =============================================================================
*/
typedef enum		e_shape_tabs
{
	MAIN_TAB,
	TRANSFORM_TAB,
	MATERIAL_TAB,
	COLOR_TAB,
	TEXTURE_TAB,
	SECTION_TAB
}					t_tabs;

/*
** =============================================================================
** ================ Tab for changing type/name/params of shape =================
** =============================================================================
*/
typedef struct		s_main_tab
{
	GtkWidget		*label;
	GtkWidget		*grid;
	GtkWidget		*name_label;
	GtkWidget		*name_changer;
	GtkWidget		*type_label;
	GtkWidget		*type_combo;
	GtkWidget		*params_frame;
	GtkWidget		*v_params;
	GtkWidget		*h_radius;
	t_spinner		radius;
	GtkWidget		*h_height;
	t_spinner		height;
	GtkWidget		*h_angle;
	t_spinner		angle;
}					t_main_tab;

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
** =========== Tab for changing texture and normal mapping of shape ============
** =============================================================================
*/
typedef struct		s_texture_tab
{
	GtkWidget		*label;
	GtkWidget		*grid;
	GtkWidget		*texture_label;
	GtkWidget		*texture_combo;
	GtkWidget		*normals_label;
	GtkWidget		*normals_combo;
}					t_texture_tab;

/*
** =============================================================================
** ====================== Tab for changing color of shape ======================
** =============================================================================
*/
typedef struct		s_color_tab
{
	GtkWidget		*label;
	GtkWidget		*scrolled_window;
	GtkWidget		*color;
}					t_color_tab;

/*
** =============================================================================
** =============== Tab for changing section properties of shape ================
** =============================================================================
*/
typedef struct		s_section_tab
{
	GtkWidget		*label;
	GtkWidget		*scrolled_window;
	GtkWidget		*grid;
	GtkWidget		*style_frame;
	GtkWidget		*style_grid;
	GtkWidget		*style_simple;
	GtkWidget		*style_complex;
	GtkWidget		*centre_button;
	GtkWidget		*tree;
	GtkTreeStore	*store;
	GtkTreeModel	*model;
	GtkTreeIter		iter[SECTION_CNT];
	GTK_SELECT		*select;
	GtkListStore	*type_store;
	GtkCellRenderer	*toggle_on_renderer;
	GtkCellRenderer	*combo_renderer;
	GtkWidget		*pos_grid;
	GtkWidget		*pos_label;
	t_spinner		pos_x;
	t_spinner		pos_y;
	t_spinner		pos_z;
	GtkWidget		*addition_v_box;
	GtkWidget		*sphere_grid;
	t_spinner		radius;
	GtkWidget		*plane_grid;
	GtkWidget		*dir_label;
	GtkWidget		*spin_dir_x;
	GtkWidget		*spin_dir_y;
	GtkWidget		*spin_dir_z;
}					t_section_tab;
/*
** ========================= Columns for sections tree =========================
*/
typedef enum		e_sections_column
{
	SEC_ON_COL,
	SEC_TYPE_COL,
	SEC_POINTER_COL,
	SEC_COL_CNT
}					t_sections_column;


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
	t_main_tab		main;
	t_transform_tab	transform;
	t_material_tab	material;
	t_color_tab		color;
	t_section_tab	section;
	t_texture_tab	texture;
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
	GtkWidget		*filter_label;
	GtkWidget		*filter_combo;
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
	t_gtk_textures	normals;
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
** ======================== Entity for calculating blur ========================
** =============================================================================
*/
typedef struct		s_blur
{
	cl_uint3		average;
	cl_uint			segment_size;
	cl_int2			count_of_segments;
	cl_int2			segment;
	cl_int2			pix_of_segment;
	cl_int			pix;
}					t_blur;

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
									cl_uchar4 *dto_buffer);
void				gtk_set_ui_widgets(t_ui *ui);
void				gtk_set_shape_widgets(t_gtk_shape **gtk_shape,
									SCENE *scene);
void				gtk_set_shapes_tree(t_gtk_shapes *shapes, t_rt *rt);
void				gtk_set_textures_tree(t_gtk_textures *textures,
									const char *name, PPM_IMG *ppm);
void				gtk_set_settings_widgets(t_gtk_settings *settings,
									t_rt *rt);
void				gtk_set_spin_button_for_float(GtkWidget **spin,
									cl_float value);
void				gtk_set_spin_button_for_one(GtkWidget **spin,
									cl_float value);
void				gtk_set_spin_button_for_radius(GtkWidget **spin,
									cl_float value);
void				gtk_set_spin_button_for_angle(GtkWidget **spin,
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
void				spin_button_section_position_changer(GtkSpinButton *button,
									gpointer data);
void				spin_button_section_radius_changer(GtkSpinButton *button,
									gpointer data);
void				spin_button_section_direction_changer(GtkSpinButton *button,
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
** ============================== Sections motion ==============================
*/
void				move_sections_by_camera_movement(DTO_SHAPE *dto,
										DTO_CAM *cam, guint key);
void				move_sections_by_mouse(FLT3 diff, SECTION *sections);
void				rotate_sections(DTO_SHAPE *dto, DTO_CAM *cam,
										cl_float angle, guint key);

/*
** ======================== Change the shape parameters ========================
*/
_Bool				do_change_shape_param(FLT3 *params, SHAPE_TYPE type,
										int diff);
void				change_shape_param(t_rt *rt);
/*
** ============================== Update widgets ===============================
*/
gboolean			update_shape_widget(gpointer data);
void				update_gtk_shape_sec_spins(t_section_tab *tab,
										SECTION *section);
/*
** ============================== Compute filter ===============================
*/
void				compute_filter(t_rt *rt);
void				compute_blur(t_rt *rt);
void				put_pixel_to_average_sum(cl_uchar4 *pixel,
										cl_uint3 *average);
cl_uint3			get_average_from_sum(cl_uint3 *average_sum,
										cl_uint count_of_pixels);
void				put_average_to_pixel(cl_uchar4 *pixel, cl_uint3 *average);
cl_uchar4			calc_matrix_values(const int matrix[9], int i, t_rt *rt);

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
