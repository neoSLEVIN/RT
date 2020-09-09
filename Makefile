DEFINED_VAR = -DPROJ_DIR=\"$(shell pwd)\"

NAME = RT

RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
PURPLE = \033[35m
CYAN = \033[36m
NONE = \033[0m


INCLUDE_DIR = -Iinclude/ -Ilibraries/jcparser/include/ -Ilibraries/libft/inc/ -Ilibraries/oclmath/include/
LIBRARIES = -ljcparser -L./libraries/jcparser/ -lft -L./libraries/libft/ -lftprintf -L./libraries/libft/src/libftprintf -loclmath -L./libraries/oclmath

OPEN_CL_MODULE = source/opencl/utils/error_cl.c \
        source/opencl/utils/new_ocl.c \
        source/opencl/commands/init_ocl.c \
        source/opencl/commands/create_cl.c \
        source/opencl/commands/compile_cl.c \
        source/opencl/commands/setting_cl.c \
        source/opencl/commands/run_cl.c \
        source/opencl/settings/translate_data.c \
        source/opencl/settings/set_memory.c \
        source/opencl/settings/set_kernel_args.c \
        source/opencl/settings/realloc_data.c \
        source/opencl/settings/update_args.c \
        source/opencl/settings/image_import.c \
        source/opencl/settings/safe_image_import.c \
        source/opencl/utils/ppm_error_safe.c \
        source/opencl/settings/update_ppm_img_args.c \

PARSER_MODULE = source/parser/parse_scene.c \
        source/parser/parse_color.c \
        source/parser/parse_transform.c \
        source/parser/parse_material.c \
        source/parser/parse_camera.c \
        source/parser/parse_cl_float3.c \
        source/parser/parse_type.c \
        source/parser/parse_error.c \
        source/parser/parse_shape.c \
        source/parser/parse_light.c \
        source/parser/parse_settings.c \
        source/parser/parse_textures.c \
        source/parser/parse_sections.c \
        source/parser/parser_utils.c \

GTK_MODULE = source/gtk/utils/init_info.c \
        source/gtk/utils/new_scene.c \
        source/gtk/utils/new_gtk.c \
        source/gtk/utils/clear_rt.c \
        source/gtk/utils/cleaner.c \
        source/serializer/serialize_type_name.c \
        source/gtk/settings/gtk_set_main_window.c \
        source/gtk/settings/gtk_set_widgets.c \
        source/gtk/settings/gtk_set_signals.c \
        source/gtk/settings/gtk_set_positions.c \
        source/gtk/widgets/gtk_set_shapes_widgets.c \
        source/gtk/widgets/gtk_set_ui_widgets.c \
        source/gtk/widgets/gtk_set_shape_widgets.c \
        source/gtk/widgets/gtk_set_spin_button.c \
        source/gtk/widgets/gtk_set_image_widgets.c \
        source/gtk/widgets/gtk_set_settings_widgets.c \
        source/gtk/widgets/gtk_set_textures_widgets.c \
        source/gtk/positions/gtk_set_settings_positions.c \
        source/gtk/positions/gtk_set_shapes_positions.c \
        source/gtk/callbacks/escape_window.c \
        source/gtk/callbacks/press_key_on_window.c \
        source/gtk/callbacks/release_key_on_window.c \
        source/gtk/callbacks/button_on_image_event_box.c \
        source/gtk/callbacks/fps_scale_moved.c \
        source/gtk/callbacks/change_axis.c \
        source/gtk/callbacks/draw_by_timeout.c \
        source/gtk/callbacks/shapes_tree_double_click.c \
        source/gtk/actions/update_marker.c \
        source/gtk/actions/holders_cnt.c \
        source/gtk/actions/make_action.c \
        source/gtk/actions/draw_image.c \
        source/gtk/actions/get_shape_id.c \
        source/gtk/actions/camera_with_shape.c \
        source/gtk/actions/camera_motion.c \
        source/gtk/actions/shape_motions/rotate_shape.c \
        source/gtk/actions/change_shape_param.c \
        source/gtk/signals/gtk_set_motions_signals.c \
        source/gtk/signals/gtk_set_ui_settings_signals.c \
        source/gtk/signals/gtk_set_shapes_signals.c \
        source/gtk/callbacks/shapes_tree_selection_changer.c \
        source/gtk/actions/update_shape_widget.c \
        source/gtk/signals/gtk_set_shape_signals.c \
        source/gtk/callbacks/shape/spin_button_section_radius_changer.c \
        source/gtk/actions/update_flags.c \
        source/gtk/actions/sections_motion.c \
        source/gtk/actions/filters/compute_filter.c \
        source/gtk/actions/filters/compute_blur.c \
        source/gtk/actions/filters/blur_functions.c \
        source/gtk/actions/filters/matrix_functions.c \
        source/gtk/utils/init_default_shape_dto.c \
        source/gtk/callbacks/new_shape.c \
        source/gtk/widgets/gtk_set_lights_widgets.c \
        source/gtk/positions/gtk_set_lights_positions.c \
        source/gtk/signals/gtk_set_lights_signals.c \
        source/gtk/callbacks/lights_tree_selection_changer.c \
        source/gtk/callbacks/shapes_tree_single_click.c \
        source/gtk/callbacks/lights_tree_single_click.c \
        source/gtk/widgets/gtk_set_light_widgets.c \
        source/gtk/positions/gtk_set_light_positions.c \
        source/gtk/actions/update_light_widget.c \
        source/gtk/signals/gtk_set_light_signals.c \
        source/gtk/callbacks/light/light_expander_callback.c \
        source/gtk/callbacks/shape/shape_expander_callback.c \
        source/gtk/callbacks/shape/switch_page_shape_notebook.c \
        source/gtk/callbacks/shape/shape_material_scale_moved.c \
        source/gtk/callbacks/shape/cell_editable_holders.c \
        source/gtk/callbacks/shape/section_callbacks.c \
        source/gtk/callbacks/shape/color_activated_changer.c \
        source/gtk/callbacks/shape/changing_shape_type.c \
        source/gtk/callbacks/shape/changing_textures_normals.c \
        source/gtk/callbacks/shape/press_key_on_shape_name.c \
        source/gtk/callbacks/light/press_key_on_light_name.c \
        source/gtk/callbacks/light/changing_light_type.c \
        source/gtk/signals/gtk_set_buttons_signals.c \
        source/gtk/widgets/gtk_set_buttons_widgets.c \
        source/gtk/positions/gtk_set_textures_positions.c \
        source/gtk/positions/gtk_set_buttons_positions.c \
        source/gtk/callbacks/shape/spin_button_shape_angle_changer.c \
        source/gtk/callbacks/shape/spin_button_shape_height_changer.c \
        source/gtk/callbacks/shape/spin_button_shape_radius_changer.c \
        source/gtk/actions/new_shape_update_everything.c \
        source/gtk/callbacks/shape/spin_button_shape_position_changer.c \
        source/gtk/callbacks/shape/spin_button_section_position_changer.c \
        source/gtk/callbacks/shape/spin_button_section_direction_changer.c \
        source/gtk/callbacks/light/spin_button_light_intensity_changer.c \
        source/gtk/callbacks/light/spin_button_light_position_changer.c \
        source/gtk/callbacks/light/spin_button_light_direction_changer.c \
        source/gtk/callbacks/new_light.c \
        source/gtk/callbacks/changing_filter_type.c \
        source/gtk/positions/gtk_set_shape_positions.c \
        source/gtk/positions/shape_positions/gtk_set_shape_main_positions.c \
        source/gtk/positions/shape_positions/gtk_set_shape_transform_positions.c \
        source/gtk/positions/shape_positions/gtk_set_shape_material_positions.c \
        source/gtk/positions/shape_positions/gtk_set_shape_texture_positions.c \
        source/gtk/positions/shape_positions/gtk_set_shape_color_positions.c \
        source/gtk/positions/shape_positions/gtk_set_shape_section_positions.c \
        source/gtk/callbacks/copy_paste_shape.c \
        source/gtk/utils/usage.c \
        source/gtk/utils/get_default_shape.c \
        source/gtk/actions/restart_position.c \
        source/gtk/actions/make_update_args.c \
        source/gtk/widgets/shape_tabs/gtk_set_main_tab_widgets.c \
        source/gtk/widgets/shape_tabs/gtk_set_transform_tab_widgets.c \
        source/gtk/widgets/shape_tabs/gtk_set_material_tab_widgets.c \
        source/gtk/widgets/shape_tabs/gtk_set_color_tab_widgets.c \
        source/gtk/widgets/shape_tabs/gtk_set_texture_tab_widgets.c \
        source/gtk/widgets/shape_tabs/gtk_set_sections_tab_widgets.c \
        source/gtk/widgets/shape_tabs/gtk_set_sections_tab_tree_widgets.c \
        source/gtk/actions/shape_tabs/update_gtk_shape_position.c \
        source/gtk/actions/shape_tabs/update_gtk_shape_material.c \
        source/gtk/actions/shape_tabs/update_gtk_shape_color.c \
        source/gtk/actions/shape_tabs/update_gtk_shape_main.c \
        source/gtk/actions/shape_tabs/update_gtk_shape_texture.c \
        source/gtk/actions/shape_tabs/update_gtk_shape_section.c \
        source/parser/parse_shape_param_by_type.c \
        source/gtk/actions/get_new_file_name.c \
        source/gtk/callbacks/save_image.c \
        source/gtk/utils/show_widgets.c \
        source/gtk/callbacks/spin_button_filter_changer.c \
        source/gtk/widgets/gtk_set_setting_filter_widgets.c \
        source/gtk/callbacks/fov_scale_moved.c \
        source/gtk/utils/get_angle_by_diff.c \
        source/gtk/widgets/gtk_set_camera_widgets.c \
        source/gtk/positions/gtk_set_camera_positions.c \
        source/gtk/signals/gtk_set_camera_signals.c \
        source/gtk/callbacks/display_scale_moved.c \
        source/gtk/callbacks/spin_button_camera_position_changer.c \
        source/gtk/actions/update_camera_widget.c \
        source/gtk/callbacks/camera_expander_callback.c \
        source/gtk/widgets/gtk_set_scale_widgets.c \
        source/gtk/callbacks/new_ppm_img.c \
        source/gtk/actions/error_message_dialog.c \
        source/gtk/actions/new_ppm_img_init.c \
        source/gtk/actions/new_ppm_img_update_everything.c \
        source/gtk/signals/gtk_set_textures_signals.c \
        source/gtk/callbacks/ppm_img_tree_single_click.c \
        source/gtk/actions/delete_ppm_img.c \
        source/gtk/actions/shape_motions/move_shape_by_camera_movement.c \
        source/gtk/actions/shape_motions/move_shape_by_camera_rotating.c \
        source/gtk/actions/shape_motions/move_shape_by_mouse.c \
        source/gtk/callbacks/shape/spin_button_shape_width_changer.c \
        source/gtk/signals/gtk_set_triangle_dots_signals.c \
        source/gtk/callbacks/shape/spin_button_shape_dot_a_changer.c \
        source/gtk/callbacks/shape/spin_button_shape_dot_b_changer.c \
        source/gtk/callbacks/shape/spin_button_shape_dot_c_changer.c \
        source/gtk/callbacks/shape/spin_button_shape_depth_changer.c \
        source/gtk/callbacks/shape/spin_button_shape_shift_changer.c \
		source/gtk/actions/do_change_shape_param.c \

SERIALIZER_MODULE = source/gtk/actions/serialize_scene_to_json.c \
        source/serializer/api/serialize_str.c \
        source/serializer/api/serialize_value.c \
        source/serializer/serialize_settings.c \
        source/serializer/serialize_start.c \
        source/gtk/callbacks/save_scene.c \
        source/serializer/serialize_scene.c \
        source/serializer/api/serialize_name.c \
        source/serializer/api/serialize_indent.c \
        source/serializer/api/serialize_open.c \
        source/serializer/api/serialize_close.c \
        source/serializer/api/serialize_base.c \
        source/serializer/api/serialize_comma.c \
        source/serializer/serialize_camera.c \
        source/serializer/serialize_float3.c \
        source/serializer/serialize_lights.c \
        source/serializer/serialize_ppm_img.c \
        source/serializer/serialize_shapes.c \
        source/serializer/serialize_transform.c \
        source/serializer/serialize_material.c \
        source/serializer/serialize_sections.c \
        source/serializer/serialize_reserved_ppm_names.c \
        source/serializer/serialize_int2.c \


FLAGS = -g -Wall -Wextra -Werror
CC = gcc
#headers file should be add at compile time from .c to .o
GTKCFLAGS = $(shell pkg-config --cflags gtk+-3.0)
#libs at linking time from .o to exe
GTKLIBS = $(shell pkg-config --libs gtk+-3.0)

OBJ_DIR = ./obj/
ALL_MODULES = $(OPEN_CL_MODULE) $(PARSER_MODULE) $(GTK_MODULE) $(SERIALIZER_MODULE) main.c
OBJ_FILES = $(addprefix $(OBJ_DIR), $(ALL_MODULES:.c=.o))

JCPARSER_DIR = libraries/jcparser/
LIBFT_DIR = libraries/libft/
LIBFTPRINTF_DIR = libraries/libft/src/libftprintf/
OCLMATH_DIR = libraries/oclmath/

OPENCL_LIB = -framework OpenCL

all : dependency $(NAME)

dependency:
	@$(MAKE) -C $(JCPARSER_DIR)
	@$(MAKE) -C $(LIBFT_DIR)
	@$(MAKE) -C $(LIBFTPRINTF_DIR)
	@$(MAKE) -C $(OCLMATH_DIR)

$(NAME): $(OBJ_DIR) $(OBJ_FILES)
	$(CC) $(FLAGS) $(INCLUDE_DIR) $(GTKCFLAGS) $(OBJ_FILES) -o RT $(GTKLIBS) $(OPENCL_LIB) $(LIBRARIES)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o : %.c
	@mkdir -p $(@D)
	$(CC) $(DEFINED_VAR) -c $(GTKCFLAGS) $(INCLUDE_DIR) $< -o $@

clean: 
	rm -f $(OBJ_FILES)

fclean: clean
	rm -f $(NAME)

re: fclean all