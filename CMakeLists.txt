cmake_minimum_required(VERSION 3.13)
project(RT C)

set(CMAKE_C_STANDARD 99)

# магия эпл. Почему надо вызвать FIND_PACKAGE два раза мне не понятно
# особенность которую я откапал на stackoverflow:
#     link_directories надо вызвать перед add_executable
if (APPLE)
    FIND_PACKAGE(PkgConfig REQUIRED)
    PKG_CHECK_MODULES(GTK3 REQUIRED gtk+-3.0)
    INCLUDE_DIRECTORIES(${GTK3_INCLUDE_DIRS})
    LINK_DIRECTORIES(${GTK3_LIBRARY_DIRS})
    #в PROJ_DIR будет храниться путь до проекта
    add_definitions(-DPROJ_DIR="$(CMAKE_SOURCE_DIR)/")
endif()

# ==============================================================================
# ================================= Libraries ==================================
# =========================== LIBFT JCPARSER OCLMATH ===========================
# ==============================================================================
set(LIBRARIES libraries)
include_directories(${LIBRARIES})

# ==============================================================================
# =================================== LIBFT ====================================
# ==============================================================================
set(LIBFT ${LIBRARIES}/libft)
include_directories(${LIBFT})

set(LIBFT_INC ${LIBFT}/inc)
include_directories(${LIBFT_INC})

set(INCNAME_LIBFT
        libraries/libft/inc/libft.h
        libraries/libft/inc/ftprintf.h
)

set(LIBFT_SRC ${LIBFT}/src)
include_directories(${LIBFT_SRC})

set(SRCNAME_LIBFT
        libraries/libft/src/ft_strlen.c
        libraries/libft/src/ft_strlcat.c
        libraries/libft/src/ft_memcmp.c
        libraries/libft/src/ft_atoi.c
        libraries/libft/src/ft_isascii.c
        libraries/libft/src/ft_isprint.c
        libraries/libft/src/ft_tolower.c
        libraries/libft/src/ft_toupper.c
        libraries/libft/src/ft_isalnum.c
        libraries/libft/src/ft_isalpha.c
        libraries/libft/src/ft_isdigit.c
        libraries/libft/src/ft_strcmp.c
        libraries/libft/src/ft_strncmp.c
        libraries/libft/src/ft_strdup.c
        libraries/libft/src/ft_strchr.c
        libraries/libft/src/ft_strrchr.c
        libraries/libft/src/ft_strstr.c
        libraries/libft/src/ft_strnstr.c
        libraries/libft/src/ft_strcat.c
        libraries/libft/src/ft_strncat.c
        libraries/libft/src/ft_strcpy.c
        libraries/libft/src/ft_strncpy.c
        libraries/libft/src/ft_bzero.c
        libraries/libft/src/ft_memset.c
        libraries/libft/src/ft_memchr.c
        libraries/libft/src/ft_memcpy.c
        libraries/libft/src/ft_memccpy.c
        libraries/libft/src/ft_memmove.c
        libraries/libft/src/ft_memalloc.c
        libraries/libft/src/ft_memdel.c
        libraries/libft/src/ft_strnew.c
        libraries/libft/src/ft_strdel.c
        libraries/libft/src/ft_strclr.c
        libraries/libft/src/ft_striter.c
        libraries/libft/src/ft_striteri.c
        libraries/libft/src/ft_strmap.c
        libraries/libft/src/ft_strmapi.c
        libraries/libft/src/ft_strequ.c
        libraries/libft/src/ft_strnequ.c
        libraries/libft/src/ft_strsub.c
        libraries/libft/src/ft_strjoin.c
        libraries/libft/src/ft_strtrim.c
        libraries/libft/src/ft_strsplit.c
        libraries/libft/src/ft_itoa.c
        libraries/libft/src/ft_putchar.c
        libraries/libft/src/ft_putstr.c
        libraries/libft/src/ft_putendl.c
        libraries/libft/src/ft_putnbr.c
        libraries/libft/src/ft_putchar_fd.c
        libraries/libft/src/ft_putstr_fd.c
        libraries/libft/src/ft_putendl_fd.c
        libraries/libft/src/ft_putnbr_fd.c
        libraries/libft/src/ft_lstnew.c
        libraries/libft/src/ft_lstdelone.c
        libraries/libft/src/ft_lstdel.c
        libraries/libft/src/ft_lstadd.c
        libraries/libft/src/ft_lstiter.c
        libraries/libft/src/ft_lstmap.c
        libraries/libft/src/ft_abs.c
        libraries/libft/src/ft_dabs.c
        libraries/libft/src/ft_strrev.c
        libraries/libft/src/ft_lstlen.c
        libraries/libft/src/ft_lstsplit.c
        libraries/libft/src/ft_lstabi.c
        libraries/libft/src/ft_wordcnt.c
        libraries/libft/src/ft_strstrsplit.c
        libraries/libft/src/get_next_line.c
        libraries/libft/src/ft_itoa_base.c
        libraries/libft/src/ft_printf.c
        libraries/libft/src/ft_del.c
        libraries/libft/src/ft_dlstnew.c
        libraries/libft/src/ft_dlstdel.c
        libraries/libft/src/ft_dlstdelone.c
        libraries/libft/src/ft_dlstsplit.c
        libraries/libft/src/ft_dlstargv.c
        libraries/libft/src/ft_dlstlen.c
        libraries/libft/src/ft_strlen.c
        libraries/libft/src/ft_strlcat.c
        libraries/libft/src/ft_error.c
        libraries/libft/src/ft_strsplit_del.c
        libraries/libft/src/ft_get_text_file.c
        libraries/libft/src/ft_str_to_upper.c
        libraries/libft/src/ft_strlen_rus.c)

set(LIBFTPRINTF_SRC ${LIBFT_SRC}/libftprintf)
include_directories(${LIBFTPRINTF_SRC})

set(SRCNAME_LIBFTPRINTF
        libraries/libft/src/libftprintf/pft_validator.c
        libraries/libft/src/libftprintf/pft_parser.c
        libraries/libft/src/libftprintf/pft_parse_addition.c
        libraries/libft/src/libftprintf/pft_parse_flag.c
        libraries/libft/src/libftprintf/pft_parse_width.c
        libraries/libft/src/libftprintf/pft_parse_precision.c
        libraries/libft/src/libftprintf/pft_parse_length.c
        libraries/libft/src/libftprintf/pft_parse_type.c
        libraries/libft/src/libftprintf/pft_color.c
        libraries/libft/src/libftprintf/pft_choose_type.c
        libraries/libft/src/libftprintf/pft_print_wchar.c
        libraries/libft/src/libftprintf/pft_print_indent.c
        libraries/libft/src/libftprintf/pft_print_d.c
        libraries/libft/src/libftprintf/pft_print_u.c
        libraries/libft/src/libftprintf/pft_print_o.c
        libraries/libft/src/libftprintf/pft_print_x.c
        libraries/libft/src/libftprintf/pft_print_f.c
        libraries/libft/src/libftprintf/pft_print_c.c
        libraries/libft/src/libftprintf/pft_print_s.c
        libraries/libft/src/libftprintf/pft_print_p.c
        libraries/libft/src/libftprintf/pft_print_percent.c
        libraries/libft/src/libftprintf/pft_print_other.c
        libraries/libft/src/libftprintf/pft_calculator.c
        libraries/libft/src/libftprintf/pft_calculate_f.c
        libraries/libft/src/libftprintf/pft_cleaner.c
)

# ==============================================================================
# ================================= JCPARSER ===================================
# ==============================================================================
set(JC_PARSER ${LIBRARIES}/jcparser)
include_directories(${JC_PARSER})

set(JC_PARSER_INC ${JC_PARSER}/include)
include_directories(${JC_PARSER_INC})

set(INCNAME_JC_PARSER
        libraries/jcparser/include/jc_parser.h
        libraries/jcparser/include/jcp_parser.h
        libraries/jcparser/include/jc_data.h
)

set(JC_PARSER_SRC ${LIBRARIES}/jcparser)
include_directories(${JC_PARSER_SRC})

set(SRCNAME_JC_PARSER
        libraries/jcparser/private/jcp_create_t_jcp_object.c
        libraries/jcparser/private/jcp_skip_whitespaces.c
        libraries/jcparser/private/jcp_free_tree.c
        libraries/jcparser/private/jcp_get_main_object.c
        libraries/jcparser/private/jcp_get_elem_by_idx.c
        libraries/jcparser/private/jcp_check_for_number.c
        libraries/jcparser/private/jcp_get_value_of_obj_or_arr.c
        libraries/jcparser/private/jcp_get_value_of_null.c
        libraries/jcparser/private/jcp_get_value_of_bool.c
        libraries/jcparser/private/jcp_get_value_of_str.c
        libraries/jcparser/private/jcp_get_value_of_num.c
        libraries/jcparser/private/jcp_get_value_by_type.c
        libraries/jcparser/private/jcp_get_object_name.c
        libraries/jcparser/private/jcp_get_element.c
        libraries/jcparser/private/jcp_get_object.c
        libraries/jcparser/private/jcp_parent_dot_child.c
        libraries/jcparser/private/jcp_get_obj_by_key.c
        libraries/jcparser/private/jcp_field_with_index.c
        libraries/jcparser/private/jcp_str_of_types.c
        libraries/jcparser/private/jcp_print_bad_type_error.c
        libraries/jcparser/api/jc_get_float.c
        libraries/jcparser/api/jc_get_field.c
        libraries/jcparser/api/jc_clear_all.c
        libraries/jcparser/api/jc_get_string.c
        libraries/jcparser/api/jc_additional_utils.c
        libraries/jcparser/api/jc_get_bool.c)

# ==============================================================================
# ================================== OCLMATH ===================================
# ==============================================================================
set(OCLMATH ${LIBRARIES}/oclmath)
include_directories(${OCLMATH})

set(OCLMATH_INC ${OCLMATH}/include)
include_directories(${OCLMATH_INC})

set(INCNAME_OCLMATH
        libraries/oclmath/include/ocl_math.h
)

set(OCLMATH_SRC ${OCLMATH}/source)
include_directories(${OCLMATH_SRC})

set(SRCNAME_OCLMATH
        libraries/oclmath/source/rad_to_deg.c
        libraries/oclmath/source/deg_to_rad.c
        libraries/oclmath/source/v3_length.c
        libraries/oclmath/source/v3_add.c
        libraries/oclmath/source/v3_sub.c
        libraries/oclmath/source/v3_cross.c
        libraries/oclmath/source/v3_scale.c
        libraries/oclmath/source/v3_norm.c
        libraries/oclmath/source/v3_length_sq.c
        libraries/oclmath/source/v3_dot.c
        libraries/oclmath/source/v3_rotate.c
        libraries/oclmath/source/v2_dot.c
        libraries/oclmath/source/v2_det.c
        libraries/oclmath/source/v2_angle.c
        libraries/oclmath/source/v2_length.c
        libraries/oclmath/source/v2_scale.c
        libraries/oclmath/source/v2_norm.c
        libraries/oclmath/source/v3_angle_to_xz.c
        libraries/oclmath/source/i2_sub.c)

# ==============================================================================
# =============================== Project files ================================
# ============================= GTK OPENCL PARSER ==============================
# ==============================================================================
set(RT_INC include)
include_directories(${RT_INC})

set(INCNAME_RT
        include/scene.h
        include/parser.h
        include/serializer.h
        include/info.h
        include/ocl.h
        include/gtk_module.h)

set(RT_SRC source)
include_directories(${RT_SRC})

set(OPEN_CL_SRC ${RT_SRC}/opencl)
include_directories(${OPEN_CL_SRC})

set(SRCNAME_OPEN_CL
        source/opencl/utils/error_cl.c
        source/opencl/utils/new_ocl.c
        source/opencl/commands/init_ocl.c
        source/opencl/commands/create_cl.c
        source/opencl/commands/compile_cl.c
        source/opencl/commands/setting_cl.c
        source/opencl/commands/run_cl.c
        source/opencl/settings/translate_data.c
        source/opencl/settings/set_memory.c
        source/opencl/settings/set_kernel_args.c
        source/opencl/settings/realloc_data.c
        source/opencl/settings/update_args.c
        source/opencl/settings/image_import.c
        source/opencl/settings/safe_image_import.c
        source/opencl/utils/ppm_error_safe.c
        source/opencl/settings/update_ppm_img_args.c source/opencl/settings/update_args2.c)

set(PARSER_SRC ${RT_SRC}/parser)
include_directories(${PARSER_SRC})

set(SRCNAME_PARSER
        source/parser/parse_scene.c
        source/parser/parse_color.c
        source/parser/parse_transform.c
        source/parser/parse_material.c
        source/parser/parse_camera.c
        source/parser/parse_cl_float3.c
        source/parser/parse_type.c
        source/parser/parse_error.c
        source/parser/parse_shape.c
        source/parser/parse_light.c
        source/parser/parse_settings.c
        source/parser/parse_textures.c
        source/parser/parse_sections.c
        source/parser/parser_utils.c
        source/parser/parse_off/off_parse_file.c
        source/parser/parse_off/off_parse_utils.c
        source/parser/parse_off/off_parse_checker.c)

set(GTK_SRC ${RT_SRC}/gtk)
include_directories(${GTK_SRC})

set(SRCNAME_GTK
        source/gtk/utils/init_info.c
        source/gtk/utils/new_scene.c
        source/gtk/utils/new_gtk.c
        source/serializer/serialize_type_name.c
        source/gtk/settings/gtk_set_main_window.c
        source/gtk/settings/gtk_set_widgets.c
        source/gtk/settings/gtk_set_signals.c
        source/gtk/settings/gtk_set_positions.c
        source/gtk/widgets/gtk_set_shapes_widgets.c
        source/gtk/widgets/gtk_set_ui_widgets.c
        source/gtk/widgets/gtk_set_shape_widgets.c
        source/gtk/widgets/gtk_set_spin_button.c
        source/gtk/widgets/gtk_set_image_widgets.c
        source/gtk/widgets/gtk_set_settings_widgets.c
        source/gtk/widgets/gtk_set_textures_widgets.c
        source/gtk/positions/gtk_set_settings_positions.c
        source/gtk/positions/gtk_set_shapes_positions.c
        source/gtk/callbacks/escape_window.c
        source/gtk/callbacks/press_key_on_window.c
        source/gtk/callbacks/release_key_on_window.c
        source/gtk/callbacks/button_on_image_event_box.c
        source/gtk/callbacks/fps_scale_moved.c
        source/gtk/callbacks/change_axis.c
        source/gtk/callbacks/draw_by_timeout.c
        source/gtk/callbacks/shapes_tree_double_click.c
        source/gtk/actions/update_marker.c
        source/gtk/actions/holders_cnt.c
        source/gtk/actions/make_action.c
        source/gtk/actions/draw_image.c
        source/gtk/actions/get_shape_id.c
        source/gtk/actions/camera_with_shape.c
        source/gtk/actions/camera_motion.c
        source/gtk/actions/shape_motions/rotate_shape.c
        source/gtk/actions/change_shape_param.c
        source/gtk/signals/gtk_set_motions_signals.c
        source/gtk/signals/gtk_set_ui_settings_signals.c
        source/gtk/signals/gtk_set_shapes_signals.c
        source/gtk/callbacks/shapes_tree_selection_changer.c
        source/gtk/actions/update_shape_widget.c
        source/gtk/signals/gtk_set_shape_signals.c
        source/gtk/callbacks/shape/spin_button_section_radius_changer.c
        source/gtk/actions/update_flags.c
        source/gtk/actions/sections_motion.c
        source/gtk/actions/filters/compute_filter.c
        source/gtk/actions/filters/compute_blur.c
        source/gtk/actions/filters/blur_functions.c
        source/gtk/actions/filters/matrix_functions.c
        source/gtk/utils/init_default_shape_dto.c
        source/gtk/callbacks/new_shape.c
        source/gtk/widgets/gtk_set_lights_widgets.c
        source/gtk/positions/gtk_set_lights_positions.c
        source/gtk/signals/gtk_set_lights_signals.c
        source/gtk/callbacks/lights_tree_selection_changer.c
        source/gtk/callbacks/shapes_tree_single_click.c
        source/gtk/callbacks/lights_tree_single_click.c
        source/gtk/widgets/gtk_set_light_widgets.c
        source/gtk/positions/gtk_set_light_positions.c
        source/gtk/actions/update_light_widget.c
        source/gtk/signals/gtk_set_light_signals.c
        source/gtk/callbacks/light/light_expander_callback.c
        source/gtk/callbacks/shape/shape_expander_callback.c
        source/gtk/callbacks/shape/switch_page_shape_notebook.c
        source/gtk/callbacks/shape/shape_material_scale_moved.c
        source/gtk/callbacks/shape/cell_editable_holders.c
        source/gtk/callbacks/shape/section_callbacks.c
        source/gtk/callbacks/shape/changing_shape_type.c
        source/gtk/callbacks/shape/changing_textures_normals.c
        source/gtk/callbacks/shape/press_key_on_shape_name.c
        source/gtk/callbacks/light/press_key_on_light_name.c
        source/gtk/callbacks/light/changing_light_type.c
        source/gtk/signals/gtk_set_buttons_signals.c
        source/gtk/widgets/gtk_set_buttons_widgets.c
        source/gtk/positions/gtk_set_textures_positions.c
        source/gtk/positions/gtk_set_buttons_positions.c
        source/gtk/callbacks/shape/spin_button_shape_angle_changer.c
        source/gtk/callbacks/shape/spin_button_shape_height_changer.c
        source/gtk/callbacks/shape/spin_button_shape_radius_changer.c
        source/gtk/actions/new_shape_update_everything.c
        source/gtk/callbacks/shape/spin_button_shape_position_changer.c
        source/gtk/callbacks/shape/spin_button_section_position_changer.c
        source/gtk/callbacks/shape/spin_button_section_direction_changer.c
        source/gtk/callbacks/light/spin_button_light_intensity_changer.c
        source/gtk/callbacks/light/spin_button_light_position_changer.c
        source/gtk/callbacks/light/spin_button_light_direction_changer.c
        source/gtk/callbacks/new_light.c
        source/gtk/callbacks/changing_filter_type.c
        source/gtk/positions/gtk_set_shape_positions.c
        source/gtk/positions/shape_positions/gtk_set_shape_main_positions.c
        source/gtk/positions/shape_positions/gtk_set_shape_transform_positions.c
        source/gtk/positions/shape_positions/gtk_set_shape_material_positions.c
        source/gtk/positions/shape_positions/gtk_set_shape_texture_positions.c
        source/gtk/positions/shape_positions/gtk_set_shape_color_positions.c
        source/gtk/positions/shape_positions/gtk_set_shape_section_positions.c
        source/gtk/callbacks/copy_paste_shape.c
        source/gtk/utils/usage.c
        source/gtk/utils/get_default_shape.c
        source/gtk/actions/restart_position.c
        source/gtk/actions/make_update_args.c
        source/gtk/widgets/shape_tabs/gtk_set_main_tab_widgets.c
        source/gtk/widgets/shape_tabs/gtk_set_transform_tab_widgets.c
        source/gtk/widgets/shape_tabs/gtk_set_material_tab_widgets.c
        source/gtk/widgets/shape_tabs/gtk_set_color_tab_widgets.c
        source/gtk/widgets/shape_tabs/gtk_set_texture_tab_widgets.c
        source/gtk/widgets/shape_tabs/gtk_set_sections_tab_widgets.c
        source/gtk/widgets/shape_tabs/gtk_set_sections_tab_tree_widgets.c
        source/gtk/actions/shape_tabs/update_gtk_shape_position.c
        source/gtk/actions/shape_tabs/update_gtk_shape_material.c
        source/gtk/actions/shape_tabs/update_gtk_shape_color.c
        source/gtk/actions/shape_tabs/update_gtk_shape_main.c
        source/gtk/actions/shape_tabs/update_gtk_shape_texture.c
        source/gtk/actions/shape_tabs/update_gtk_shape_section.c
        source/parser/parse_shape_param_by_type.c
        source/gtk/callbacks/save_image.c
        source/gtk/utils/show_widgets.c
        source/gtk/callbacks/scale_button_filter_changer.c
        source/gtk/widgets/gtk_set_setting_filter_widgets.c
        source/gtk/callbacks/fov_scale_moved.c
        source/gtk/utils/get_angle_by_diff.c
        source/gtk/widgets/gtk_set_camera_widgets.c
        source/gtk/positions/gtk_set_camera_positions.c
        source/gtk/signals/gtk_set_camera_signals.c
        source/gtk/callbacks/display_scale_moved.c
        source/gtk/callbacks/spin_button_camera_position_changer.c
        source/gtk/actions/update_camera_widget.c
        source/gtk/callbacks/camera_expander_callback.c
        source/gtk/widgets/gtk_set_scale_widgets.c
        source/gtk/callbacks/new_ppm_img.c
        source/gtk/actions/error_message_dialog.c
        source/gtk/actions/new_ppm_img_init.c
        source/gtk/actions/new_ppm_img_update_everything.c
        source/gtk/signals/gtk_set_textures_signals.c
        source/gtk/callbacks/ppm_img_tree_single_click.c
        source/gtk/actions/delete_ppm_img.c
        source/gtk/actions/shape_motions/move_shape_by_camera_movement.c
        source/gtk/actions/shape_motions/move_shape_by_camera_rotating.c
        source/gtk/actions/shape_motions/move_shape_by_mouse.c
        source/gtk/callbacks/shape/spin_button_shape_width_changer.c
        source/gtk/signals/gtk_set_triangle_dots_signals.c
        source/gtk/callbacks/shape/spin_button_shape_dot_a_changer.c
        source/gtk/callbacks/shape/spin_button_shape_dot_b_changer.c
        source/gtk/callbacks/shape/spin_button_shape_dot_c_changer.c
        source/gtk/callbacks/shape/spin_button_shape_depth_changer.c
        source/gtk/callbacks/shape/spin_button_shape_shift_changer.c
        source/gtk/actions/do_change_shape_param.c
        source/gtk/callbacks/change_anti_aliasing.c
        source/gtk/callbacks/scale_button_settings_changer.c
        source/gtk/utils/file_chooser_utils.c
        source/gtk/utils/file_chooser.c
        source/gtk/callbacks/shape/spin_button_color_changer.c
        source/gtk/actions/do_change_off_dots.c)

set(SERIALIZER_SRC ${RT_SRC}/serializer)
include_directories(${SERIALIZER_SRC})

set(SRCNAME_SERIALIZER
        source/gtk/actions/serialize_scene_to_json.c
        source/serializer/api/serialize_str.c
        source/serializer/api/serialize_value.c
        source/serializer/serialize_settings.c
        source/serializer/serialize_start.c
        source/gtk/callbacks/save_scene.c
        source/serializer/serialize_scene.c
        source/serializer/api/serialize_name.c
        source/serializer/api/serialize_indent.c
        source/serializer/api/serialize_open.c
        source/serializer/api/serialize_close.c
        source/serializer/api/serialize_base.c
        source/serializer/api/serialize_comma.c
        source/serializer/serialize_camera.c
        source/serializer/serialize_float3.c
        source/serializer/serialize_lights.c
        source/serializer/serialize_ppm_img.c
        source/serializer/serialize_shapes.c
        source/serializer/serialize_transform.c
        source/serializer/serialize_material.c
        source/serializer/serialize_sections.c
        source/serializer/serialize_reserved_ppm_names.c
        source/serializer/serialize_int2.c)



add_executable(RT
        main.c
        ${INCNAME_LIBFT}
        ${SRCNAME_LIBFT}
        ${SRCNAME_LIBFTPRINTF}
        ${INCNAME_JC_PARSER}
        ${SRCNAME_JC_PARSER}
        ${INCNAME_OCLMATH}
        ${SRCNAME_OCLMATH}
        ${INCNAME_RT}
        ${SRCNAME_GTK}
        ${SRCNAME_SERIALIZER}
        ${SRCNAME_PARSER}
        ${SRCNAME_OPEN_CL}
)

# ==============================================================================
# ================================== KERNEL ====================================
# ==============================================================================
foreach (CLKernelName
        "include"
        "normals"
        "sections"
        "semi_intersections"
        "intersections"
        "intersections2"
        "light"
        "random"
        "reflect"
        "refract"
        "color"
        "ray"
        "ray_tracing"
        "uv_mapping"
        "uv_patterns"
        "perlin_noise"
	"filters"
)
    set (CLKernelSourceFile "kernel/${CLKernelName}.cl")
    configure_file (${CLKernelSourceFile}
            ${CMAKE_BINARY_DIR}/kernel/${CLKernelName}.cl COPYONLY)
endforeach (CLKernelName)

# ==============================================================================
# =================================== TEXTURE ==================================
# ==============================================================================
    file(GLOB PPM_TEXTURES "extras/textures/*.ppm")
    file(COPY ${PPM_TEXTURES} DESTINATION ${CMAKE_BINARY_DIR}/extras/textures)

# ==============================================================================
# ================================= NORMAL MAP =================================
# ==============================================================================
file(GLOB PPM_NORMAL_MAPS "extras/normalmaps/*.ppm")
file(COPY ${PPM_NORMAL_MAPS} DESTINATION ${CMAKE_BINARY_DIR}/extras/normalmaps)



# ------------------------------------------------------------------------------
# You shouldn't change anything below this line unless you know what you're doing
# ------------------------------------------------------------------------------

# ---------------------------- OS Specific settings ----------------------------
if (WIN32)
    message("I hope you have msys2 :)")

    add_compile_definitions(
            CL_HPP_MINIMUM_OPENCL_VERSION=120
            CL_HPP_TARGET_OPENCL_VERSION=200)

    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GTK REQUIRED "gtk+-3.0")
    target_link_libraries(RT ${GTK_LIBRARIES})
    add_definitions(${GTK_CFLAGS} ${GTK_CFLAGS_OTHER})

    include(FindOpenCL)
    find_package(OpenCL REQUIRED)
    include_directories(${OPENCL_INCLUDE_DIR})
    target_link_libraries(RT OpenCL::OpenCL)
    add_definitions(-DCL_TARGET_OPENCL_VERSION=220)
endif()


if (APPLE)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GTK REQUIRED "gtk+-3.0")
    target_link_libraries(RT ${GTK_LIBRARIES})
    add_definitions(${GTK_CFLAGS} ${GTK_CFLAGS_OTHER})

    include(FindOpenCL)
    find_package(OpenCL REQUIRED)
    include_directories(${OPENCL_INCLUDE_DIR})
    target_link_libraries(RT OpenCL::OpenCL)
endif()
