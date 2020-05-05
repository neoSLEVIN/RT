cmake_minimum_required(VERSION 3.15)
project(RT C)

set(CMAKE_C_STANDARD 99)

set(LIBFT ./libft)
include_directories(${LIBFT})

set(LIBFT_INC ${LIBFT}/inc)
include_directories(${LIBFT_INC})

set(INCNAME_LIBFT
        libft/inc/libft.h
        libft/inc/ftprintf.h
)

set(LIBFT_SRC ${LIBFT}/src)
include_directories(${LIBFT_SRC})

set(SRCNAME_LIBFT
        libft/src/ft_strlen.c
        libft/src/ft_strlcat.c
        libft/src/ft_memcmp.c
        libft/src/ft_atoi.c
        libft/src/ft_isascii.c
        libft/src/ft_isprint.c
        libft/src/ft_tolower.c
        libft/src/ft_toupper.c
        libft/src/ft_isalnum.c
        libft/src/ft_isalpha.c
        libft/src/ft_isdigit.c
        libft/src/ft_strcmp.c
        libft/src/ft_strncmp.c
        libft/src/ft_strdup.c
        libft/src/ft_strchr.c
        libft/src/ft_strrchr.c
        libft/src/ft_strstr.c
        libft/src/ft_strnstr.c
        libft/src/ft_strcat.c
        libft/src/ft_strncat.c
        libft/src/ft_strcpy.c
        libft/src/ft_strncpy.c
        libft/src/ft_bzero.c
        libft/src/ft_memset.c
        libft/src/ft_memchr.c
        libft/src/ft_memcpy.c
        libft/src/ft_memccpy.c
        libft/src/ft_memmove.c
        libft/src/ft_memalloc.c
        libft/src/ft_memdel.c
        libft/src/ft_strnew.c
        libft/src/ft_strdel.c
        libft/src/ft_strclr.c
        libft/src/ft_striter.c
        libft/src/ft_striteri.c
        libft/src/ft_strmap.c
        libft/src/ft_strmapi.c
        libft/src/ft_strequ.c
        libft/src/ft_strnequ.c
        libft/src/ft_strsub.c
        libft/src/ft_strjoin.c
        libft/src/ft_strtrim.c
        libft/src/ft_strsplit.c
        libft/src/ft_itoa.c
        libft/src/ft_putchar.c
        libft/src/ft_putstr.c
        libft/src/ft_putendl.c
        libft/src/ft_putnbr.c
        libft/src/ft_putchar_fd.c
        libft/src/ft_putstr_fd.c
        libft/src/ft_putendl_fd.c
        libft/src/ft_putnbr_fd.c
        libft/src/ft_lstnew.c
        libft/src/ft_lstdelone.c
        libft/src/ft_lstdel.c
        libft/src/ft_lstadd.c
        libft/src/ft_lstiter.c
        libft/src/ft_lstmap.c
        libft/src/ft_abs.c
        libft/src/ft_dabs.c
        libft/src/ft_strrev.c
        libft/src/ft_lstlen.c
        libft/src/ft_lstsplit.c
        libft/src/ft_lstabi.c
        libft/src/ft_wordcnt.c
        libft/src/ft_strstrsplit.c
        libft/src/get_next_line.c
        libft/src/ft_itoa_base.c
        libft/src/ft_printf.c
        libft/src/ft_del.c
        libft/src/ft_dlstnew.c
        libft/src/ft_dlstdel.c
        libft/src/ft_dlstdelone.c
        libft/src/ft_dlstsplit.c
        libft/src/ft_dlstargv.c
        libft/src/ft_dlstlen.c
        libft/src/ft_strlen.c
        libft/src/ft_strlcat.c
        libft/src/ft_error.c
        libft/src/ft_strsplit_del.c
        libft/src/ft_get_text_file.c
        libft/src/ft_str_to_upper.c
)

set(LIBFTPRINTF_SRC ${LIBFT_SRC}/libftprintf)
include_directories(${LIBFTPRINTF_SRC})

set(SRCNAME_LIBFTPRINTF
        libft/src/libftprintf/validator.c
        libft/src/libftprintf/parser.c
        libft/src/libftprintf/parse_addition.c
        libft/src/libftprintf/parse_flag.c
        libft/src/libftprintf/parse_width.c
        libft/src/libftprintf/parse_precision.c
        libft/src/libftprintf/parse_length.c
        libft/src/libftprintf/parse_type.c
        libft/src/libftprintf/color.c
        libft/src/libftprintf/choose_type.c
        libft/src/libftprintf/print_wchar.c
        libft/src/libftprintf/print_indent.c
        libft/src/libftprintf/print_d.c
        libft/src/libftprintf/print_u.c
        libft/src/libftprintf/print_o.c
        libft/src/libftprintf/print_x.c
        libft/src/libftprintf/print_f.c
        libft/src/libftprintf/print_c.c
        libft/src/libftprintf/print_s.c
        libft/src/libftprintf/print_p.c
        libft/src/libftprintf/print_percent.c
        libft/src/libftprintf/print_other.c
        libft/src/libftprintf/calculator.c
        libft/src/libftprintf/calculate_f.c
        libft/src/libftprintf/cleaner.c
)

set(RT_INC ./inc)
include_directories(${RT_INC})
include_directories(./src/parser/jcparser/include)

set(INCNAME_RT
        inc/ocl.h
        inc/rt.h
        inc/parser.h
        inc/scene.h
        inc/gtk_module.h
        src/parser/jcparser/include/jc_parser.h
        src/parser/jcparser/include/jcp_parser.h
        src/parser/jcparser/include/jc_data.h
)

set(RT_SRC ./src)
include_directories(${RT_SRC})

set(OPEN_CL_SRC ${RT_SRC}/opencl)
include_directories(${OPEN_CL_SRC})

set(SRCNAME_OPEN_CL
        src/opencl/error_cl.c
        src/opencl/new_ocl.c
        src/opencl/init_ocl.c
        src/opencl/create_cl.c
        src/opencl/compile_cl.c
        src/opencl/set_params_cl.c
        src/opencl/run_cl.c
)

set(PARSER_SRC ${RT_SRC}/parser)
include_directories(${PARSER_SRC})

set(SRCNAME_PARSER
        src/parser/parse_scene.c
        src/parser/parse_color.c
        src/parser/parse_transform.c
        src/parser/parse_material.c
        src/parser/parse_camera.c
        src/parser/parse_cl_float3.c
        src/parser/parse_type.c
        src/parser/parse_error.c
        src/parser/parse_shape.c
        src/parser/parse_standard_shapes.c
        src/parser/parse_light.c
        src/parser/parse_standard_lights.c
)

set(JC_PARSER_SRC ${PARSER_SRC}/jcparser)
include_directories(${JC_PARSER_SRC})

set(SRCNAME_JC_PARSER
        src/parser/jcparser/private/jcp_create_t_jcp_object.c
        src/parser/jcparser/private/jcp_skip_whitespaces.c
        src/parser/jcparser/private/jcp_free_tree.c
        src/parser/jcparser/private/jcp_get_main_object.c
        src/parser/jcparser/private/jcp_get_elem_by_idx.c
        src/parser/jcparser/private/jcp_check_for_number.c
        src/parser/jcparser/private/jcp_get_value_of_obj_or_arr.c
        src/parser/jcparser/private/jcp_get_value_of_null.c
        src/parser/jcparser/private/jcp_get_value_of_bool.c
        src/parser/jcparser/private/jcp_get_value_of_str.c
        src/parser/jcparser/private/jcp_get_value_of_num.c
        src/parser/jcparser/private/jcp_get_value_by_type.c
        src/parser/jcparser/private/jcp_get_object_name.c
        src/parser/jcparser/private/jcp_get_element.c
        src/parser/jcparser/private/jcp_get_object.c
        src/parser/jcparser/private/jcp_parent_dot_child.c
        src/parser/jcparser/private/jcp_get_obj_by_key.c
        src/parser/jcparser/private/jcp_field_with_index.c
        src/parser/jcparser/api/jc_get_float.c
        src/parser/jcparser/api/jc_get_field.c
        src/parser/jcparser/api/jc_clear_all.c
        src/parser/jcparser/api/jc_get_string.c
        src/parser/jcparser/api/jc_additional_utils.c
)

set(GTK_SRC ${RT_SRC}/gtk)
include_directories(${GTK_SRC})

set(SRCNAME_GTK
        src/gtk/new_scene.c
        src/gtk/draw_image.c
        src/gtk/new_gtk.c
        src/gtk/gtk_set_objects.c
        src/gtk/gtk_set_signals.c
        src/gtk/gtk_set_positions.c
        src/gtk/gtk_set_main_window.c
        src/gtk/gtk_set_default_params.c
)

set(RT_RT_SRC ${RT_SRC}/rt)
include_directories(${RT_RT_SRC})

set(SRCNAME_RT_RT
        src/rt/rt_del.c
        src/rt/rt_init.c
)

add_executable(RT
        main.c
        ${INCNAME_LIBFT}
        ${SRCNAME_LIBFT}
        ${SRCNAME_LIBFTPRINTF}
        ${INCNAME_RT}
        ${SRCNAME_RT_RT}
        ${SRCNAME_GTK}
        ${SRCNAME_JC_PARSER}
        ${SRCNAME_PARSER}
        ${SRCNAME_OPEN_CL}
)

foreach (CLKernelName "ray_tracing")
    set (CLKernelSourceFile "kernel/${CLKernelName}.cl")
    configure_file (${CLKernelSourceFile}
            ${CMAKE_BINARY_DIR}/kernel/${CLKernelName}.cl COPYONLY)
endforeach (CLKernelName)

# ------------------------------------------------------------------------------
# You shouldn't change anything below this line unless you know what you're doing
# ------------------------------------------------------------------------------

# ---------------------------- OS Specific settings ----------------------------
add_compile_definitions (
        CL_HPP_MINIMUM_OPENCL_VERSION=120
        CL_HPP_TARGET_OPENCL_VERSION=200
)

if (WIN32)
    if (NOT ("$ENV{INTELOCLSDKROOT}" STREQUAL ""))
        # Use the Intel SDK
        set (WINDOWS_OPEN_CL_LIB_LOCATION "$ENV{INTELOCLSDKROOT}/lib/x64")
        include_directories ("$ENV{INTELOCLSDKROOT}/include")
        message ("Using Intel OpenCL SDK")
    elseif (NOT ("$ENV{CUDA_LIB_PATH}" STREQUAL ""))
        # Use the NVIDIA SDK
        set (WINDOWS_OPEN_CL_LIB_LOCATION $ENV{CUDA_LIB_PATH})
        include_directories ($ENV{CUDA_INC_PATH})
        message ("Using NVIDIA OpenCL SDK")
    elseif (NOT("$ENV{AMDAPPSDKROOT}" STREQUAL ""))
        # Use the AMD SDK
        set (WINDOWS_OPEN_CL_LIB_LOCATION "$ENV{AMDAPPSDKROOT}/lib/x86_64")
        include_directories ("$ENV{AMDAPPSDKROOT}/include")
        message ("Using AMD OpenCL SDK")
    elseif (NOT("$ENV{OCL_ROOT}" STREQUAL ""))
        message ("Using AMD OpenCL SDK Light")

        find_package(PkgConfig REQUIRED)
        pkg_check_modules(GTK REQUIRED "gtk+-3.0")
        target_link_libraries(RT ${GTK_LIBRARIES})
        add_definitions(${GTK_CFLAGS} ${GTK_CFLAGS_OTHER})

        include(FindOpenCL)
        find_package(OpenCL REQUIRED)
        include_directories(${OPENCL_INCLUDE_DIR})
        target_link_libraries(RT OpenCL::OpenCL)
    else()
        message (FATAL_ERROR
            "Neither Intel nor NVIDIA nor AMD OpenCL SDK for Windows was found."
            "\nInstall one of those")
    endif()

endif()
