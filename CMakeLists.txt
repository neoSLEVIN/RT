cmake_minimum_required(VERSION 3.15)
project(RT C)

set(CMAKE_C_STANDARD 99)

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
)

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
        libraries/jcparser/api/jc_get_float.c
        libraries/jcparser/api/jc_get_field.c
        libraries/jcparser/api/jc_clear_all.c
        libraries/jcparser/api/jc_get_string.c
        libraries/jcparser/api/jc_additional_utils.c
)

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
        libraries/oclmath/source/degrees_to_rad.c
        libraries/oclmath/source/v3_length.c
        libraries/oclmath/source/v3_add.c
        libraries/oclmath/source/v3_sub.c
        libraries/oclmath/source/v3_cross.c
        libraries/oclmath/source/v3_scale.c
        libraries/oclmath/source/v3_norm.c
        libraries/oclmath/source/v3_length_sq.c
        libraries/oclmath/source/v3_dot.c
        libraries/oclmath/source/v3_rotate.c
)

# ==============================================================================
# =============================== Project files ================================
# ============================= GTK OPENCL PARSER ==============================
# ==============================================================================
set(RT_INC include)
include_directories(${RT_INC})

set(INCNAME_RT
        include/ocl.h
        include/parser.h
        include/scene.h
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
)

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
        )

set(GTK_SRC ${RT_SRC}/gtk)
include_directories(${GTK_SRC})

set(SRCNAME_GTK
        source/gtk/utils/new_gtk.c
        source/gtk/utils/new_scene.c
        source/gtk/utils/cleaner.c
        source/gtk/utils/clear_rt.c
        source/gtk/actions/draw_image.c
        source/gtk/settings/gtk_set_objects.c
        source/gtk/settings/gtk_set_signals.c
        source/gtk/settings/gtk_set_positions.c
        source/gtk/settings/gtk_set_main_window.c
        source/gtk/utils/init_info.c source/gtk/actions/update_cam.c source/gtk/actions/holders_cnt.c source/gtk/signals/escape_window.c source/gtk/signals/key_on_window.c source/gtk/signals/button_on_image_event_box.c source/gtk/actions/make_action.c source/gtk/actions/draw_by_timeout.c source/gtk/signals/fps_scale_moved.c)

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
        ${SRCNAME_PARSER}
        ${SRCNAME_OPEN_CL}
)

# ==============================================================================
# ================================== KERNEL ====================================
# ==============================================================================
foreach (CLKernelName
        "include"
        "normals"
        "intersections"
        "light"
        "random"
        "reflect"
        "refract"
        "color"
        "ray"
        "ray_tracing"
)
    set (CLKernelSourceFile "kernel/${CLKernelName}.cl")
    configure_file (${CLKernelSourceFile}
            ${CMAKE_BINARY_DIR}/kernel/${CLKernelName}.cl COPYONLY)
endforeach (CLKernelName)

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
endif()
