cmake_minimum_required(VERSION 3.15)
project(RT C)

set(CMAKE_C_STANDARD 99)

set(LIBFT ./libft)
include_directories(${LIBFT})

set(LIBFT_INC ${LIBFT}/inc)
include_directories(${LIBFT_INC})

set(INCNAME_LIBFT
        ${LIBFT_INC}/libft.h
        ${LIBFT_INC}/ftprintf.h)

set(LIBFT_SRC ${LIBFT}/src)
include_directories(${LIBFT_SRC})

set(SRCNAME_LIBFT
        ${LIBFT_SRC}/ft_strlen.c
        ${LIBFT_SRC}/ft_strlcat.c
        ${LIBFT_SRC}/ft_memcmp.c
        ${LIBFT_SRC}/ft_atoi.c
        ${LIBFT_SRC}/ft_isascii.c
        ${LIBFT_SRC}/ft_isprint.c
        ${LIBFT_SRC}/ft_tolower.c
        ${LIBFT_SRC}/ft_toupper.c
        ${LIBFT_SRC}/ft_isalnum.c
        ${LIBFT_SRC}/ft_isalpha.c
        ${LIBFT_SRC}/ft_isdigit.c
        ${LIBFT_SRC}/ft_strcmp.c
        ${LIBFT_SRC}/ft_strncmp.c
        ${LIBFT_SRC}/ft_strdup.c
        ${LIBFT_SRC}/ft_strchr.c
        ${LIBFT_SRC}/ft_strrchr.c
        ${LIBFT_SRC}/ft_strstr.c
        ${LIBFT_SRC}/ft_strnstr.c
        ${LIBFT_SRC}/ft_strcat.c
        ${LIBFT_SRC}/ft_strncat.c
        ${LIBFT_SRC}/ft_strcpy.c
        ${LIBFT_SRC}/ft_strncpy.c
        ${LIBFT_SRC}/ft_bzero.c
        ${LIBFT_SRC}/ft_memset.c
        ${LIBFT_SRC}/ft_memchr.c
        ${LIBFT_SRC}/ft_memcpy.c
        ${LIBFT_SRC}/ft_memccpy.c
        ${LIBFT_SRC}/ft_memmove.c
        ${LIBFT_SRC}/ft_memalloc.c
        ${LIBFT_SRC}/ft_memdel.c
        ${LIBFT_SRC}/ft_strnew.c
        ${LIBFT_SRC}/ft_strdel.c
        ${LIBFT_SRC}/ft_strclr.c
        ${LIBFT_SRC}/ft_striter.c
        ${LIBFT_SRC}/ft_striteri.c
        ${LIBFT_SRC}/ft_strmap.c
        ${LIBFT_SRC}/ft_strmapi.c
        ${LIBFT_SRC}/ft_strequ.c
        ${LIBFT_SRC}/ft_strnequ.c
        ${LIBFT_SRC}/ft_strsub.c
        ${LIBFT_SRC}/ft_strjoin.c
        ${LIBFT_SRC}/ft_strtrim.c
        ${LIBFT_SRC}/ft_strsplit.c
        ${LIBFT_SRC}/ft_itoa.c
        ${LIBFT_SRC}/ft_putchar.c
        ${LIBFT_SRC}/ft_putstr.c
        ${LIBFT_SRC}/ft_putendl.c
        ${LIBFT_SRC}/ft_putnbr.c
        ${LIBFT_SRC}/ft_putchar_fd.c
        ${LIBFT_SRC}/ft_putstr_fd.c
        ${LIBFT_SRC}/ft_putendl_fd.c
        ${LIBFT_SRC}/ft_putnbr_fd.c
        ${LIBFT_SRC}/ft_lstnew.c
        ${LIBFT_SRC}/ft_lstdelone.c
        ${LIBFT_SRC}/ft_lstdel.c
        ${LIBFT_SRC}/ft_lstadd.c
        ${LIBFT_SRC}/ft_lstiter.c
        ${LIBFT_SRC}/ft_lstmap.c
        ${LIBFT_SRC}/ft_abs.c
        ${LIBFT_SRC}/ft_dabs.c
        ${LIBFT_SRC}/ft_strrev.c
        ${LIBFT_SRC}/ft_lstlen.c
        ${LIBFT_SRC}/ft_lstsplit.c
        ${LIBFT_SRC}/ft_lstabi.c
        ${LIBFT_SRC}/ft_wordcnt.c
        ${LIBFT_SRC}/ft_strstrsplit.c
        ${LIBFT_SRC}/get_next_line.c
        ${LIBFT_SRC}/ft_itoa_base.c
        ${LIBFT_SRC}/ft_printf.c
        ${LIBFT_SRC}/ft_del.c
        ${LIBFT_SRC}/ft_dlstnew.c
        ${LIBFT_SRC}/ft_dlstdel.c
        ${LIBFT_SRC}/ft_dlstdelone.c
        ${LIBFT_SRC}/ft_dlstsplit.c
        ${LIBFT_SRC}/ft_dlstargv.c
        ${LIBFT_SRC}/ft_dlstlen.c
        ${LIBFT_SRC}/ft_strlen.c
        ${LIBFT_SRC}/ft_strlcat.c
        ${LIBFT_SRC}/ft_error.c
        ${LIBFT_SRC}/ft_strsplit_del.c libft/src/ft_get_text_file.c libft/src/ft_str_to_upper.c)

set(LIBFTPRINTF_SRC ${LIBFT_SRC}/libftprintf)
include_directories(${LIBFTPRINTF_SRC})

set(SRCNAME_LIBFTPRINTF
        ${LIBFTPRINTF_SRC}/validator.c
        ${LIBFTPRINTF_SRC}/parser.c
        ${LIBFTPRINTF_SRC}/parse_addition.c
        ${LIBFTPRINTF_SRC}/parse_flag.c
        ${LIBFTPRINTF_SRC}/parse_width.c
        ${LIBFTPRINTF_SRC}/parse_precision.c
        ${LIBFTPRINTF_SRC}/parse_length.c
        ${LIBFTPRINTF_SRC}/parse_type.c
        ${LIBFTPRINTF_SRC}/color.c
        ${LIBFTPRINTF_SRC}/choose_type.c
        ${LIBFTPRINTF_SRC}/print_wchar.c
        ${LIBFTPRINTF_SRC}/print_indent.c
        ${LIBFTPRINTF_SRC}/print_d.c
        ${LIBFTPRINTF_SRC}/print_u.c
        ${LIBFTPRINTF_SRC}/print_o.c
        ${LIBFTPRINTF_SRC}/print_x.c
        ${LIBFTPRINTF_SRC}/print_f.c
        ${LIBFTPRINTF_SRC}/print_c.c
        ${LIBFTPRINTF_SRC}/print_s.c
        ${LIBFTPRINTF_SRC}/print_p.c
        ${LIBFTPRINTF_SRC}/print_percent.c
        ${LIBFTPRINTF_SRC}/print_other.c
        ${LIBFTPRINTF_SRC}/calculator.c
        ${LIBFTPRINTF_SRC}/calculate_f.c
        ${LIBFTPRINTF_SRC}/cleaner.c)

set(RT_INC ./inc)
include_directories(${RT_INC})
include_directories(./src/parser/jcparser/include)

set(INCNAME_RT
        ${RT_INC}/ocl.h
        ${RT_INC}/rt.h
        ${RT_INC}/parser.h
        ${RT_INC}/utils.h
        inc/scene.h inc/gtk_module.h src/parser/jcparser/include/jc_parser.h src/parser/jcparser/include/jcp_parser.h src/parser/jcparser/include/jc_data.h)

set(RT_SRC ./src)
include_directories(${RT_SRC})

set(OPEN_CL_SRC ${RT_SRC}/opencl)
include_directories(${OPEN_CL_SRC})

set(SRCNAME_OPEN_CL
        ${OPEN_CL_SRC}/error_cl.c
        ${OPEN_CL_SRC}/init_ocl.c
        ${OPEN_CL_SRC}/create_cl.c
        ${OPEN_CL_SRC}/compile_cl.c
        ${OPEN_CL_SRC}/set_params_cl.c
        ${OPEN_CL_SRC}/run_cl.c)

set(PARSER_SRC ${RT_SRC}/parser)
include_directories(${PARSER_SRC})

set(SRCNAME_PARSER
        src/parser/parse_scene.c src/parser/jcparser/private/jcp_parent_dot_child.c src/parser/jcparser/private/jcp_get_obj_by_key.c src/parser/jcparser/api/jc_get_float.c src/parser/parse_color.c src/parser/parse_transform.c src/parser/parse_material.c src/parser/parse_camera.c src/parser/jcparser/private/jcp_field_with_index.c src/parser/parse_cl_float3.c src/parser/jcparser/api/jc_get_field.c src/parser/parse_type.c src/parser/parse_error.c src/parser/parse_shape.c src/parser/parse_standard_shapes.c src/parser/parse_light.c src/parser/parse_standard_lights.c)

set(JC_PARSER_SRC ${PARSER_SRC}/jcparser)
include_directories(${JC_PARSER_SRC})

set(SRCNAME_JC_PARSER src/parser/jcparser/private/jcp_create_t_jcp_object.c src/parser/jcparser/private/jcp_skip_whitespaces.c src/parser/jcparser/private/jcp_free_tree.c src/parser/jcparser/private/jcp_get_main_object.c src/parser/jcparser/api/jc_clear_all.c src/parser/jcparser/private/jcp_get_elem_by_idx.c src/parser/jcparser/private/jcp_check_for_number.c src/parser/jcparser/private/jcp_get_value_of_obj_or_arr.c src/parser/jcparser/private/jcp_get_value_of_null.c src/parser/jcparser/private/jcp_get_value_of_bool.c src/parser/jcparser/private/jcp_get_value_of_str.c src/parser/jcparser/private/jcp_get_value_of_num.c src/parser/jcparser/private/jcp_get_value_by_type.c src/parser/jcparser/private/jcp_get_object_name.c src/parser/jcparser/private/jcp_get_element.c src/parser/jcparser/private/jcp_get_object.c src/parser/jcparser/api/jc_get_string.c src/parser/jcparser/api/jc_additional_utils.c)

set(GTK_SRC ${RT_SRC}/gtk)
include_directories(${GTK_SRC})

set(SRCNAME_GTK
        src/gtk/run_app.c)

set(UTILS_SRC ${RT_SRC}/utils)
include_directories(${UTILS_SRC})

set(SRCNAME_UTILS
        ${UTILS_SRC}/usage.c)

add_executable(RT
        main.c
        ${INCNAME_LIBFT}
        ${SRCNAME_LIBFT}
        ${SRCNAME_LIBFTPRINTF}
        ${INCNAME_RT}
        ${SRCNAME_UTILS}
        ${SRCNAME_GTK}
        ${SRCNAME_JC_PARSER}
        ${SRCNAME_PARSER}
        ${SRCNAME_OPEN_CL}
)

foreach (CLKernelName "ray_tracing")
    set (CLKernelSourceFile "${PROJECT_SOURCE_DIR}/src/kernel/${CLKernelName}.cl")
    configure_file (${CLKernelSourceFile} ${CMAKE_BINARY_DIR}/kernel/${CLKernelName}.cl COPYONLY)
endforeach (CLKernelName)

# ------------------------------------------------------------------------------
# You shouldn't change anything below this line unless you know what you're doing
# ------------------------------------------------------------------------------

# -------- OS Specific settings ----------
add_compile_definitions (CL_HPP_MINIMUM_OPENCL_VERSION=120 CL_HPP_TARGET_OPENCL_VERSION=200)

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
        set("C:/msys64_2/mingw64/bin")
        include_directories("C:/msys64_2/mingw64/include/gtk-3.0")

        find_package(PkgConfig REQUIRED)
        pkg_check_modules(GTK REQUIRED "gtk+-3.0")
        target_link_libraries(RT ${GTK_LIBRARIES})
        add_definitions(${GTK_CFLAGS} ${GTK_CFLAGS_OTHER})

        find_package(PkgConfig REQUIRED)
        pkg_check_modules(PC_JSON-C REQUIRED json-c)
        find_path(JSON-C_INCLUDE_DIR json.h
                HINTS ${PC_JSON-C_INCLUDEDIR} ${PC_JSON-C_INCLUDE_DIRS} PATH_SUFFIXES json-c json)
        find_library(JSON-C_LIBRARY NAMES json-c libjson-c
                HINTS ${PC_JSON-C_LIBDIR} ${PC_JSON-C_LIBRARY_DIRS})
        set(JSON-C_LIBRARIES ${JSON-C_LIBRARY})
        set(JSON-C_INCLUDE_DIRS ${JSON-C_INCLUDE_DIR})
        include(FindPackageHandleStandardArgs)
        find_package_handle_standard_args(JSON-C DEFAULT_MSG JSON-C_LIBRARY JSON-C_INCLUDE_DIR)
        mark_as_advanced(JSON-C_INCLUDE_DIR JSON-C_LIBRARY)
        include_directories(${JSON-C_INCLUDE_DIR})
        target_link_libraries(RT ${JSON-C_LIBRARIES})

        include(FindOpenCL)
        find_package(OpenCL REQUIRED)
        include_directories(${OPENCL_INCLUDE_DIR})
        target_link_libraries(RT OpenCL::OpenCL)
    else()
        message (FATAL_ERROR "Neither Intel nor NVIDIA nor AMD OpenCL SDK for Windows was found. Install one of those")
    endif()

endif()
