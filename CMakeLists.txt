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
        ${LIBFT_SRC}/ft_strlcat.c)

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

set(INCNAME_RT
        ${RT_INC}/ocl.h
        ${RT_INC}/rt.h)

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

add_executable(RT
        main.c
        ${INCNAME_LIBFT}
        ${SRCNAME_LIBFT}
        ${SRCNAME_LIBFTPRINTF}
        ${INCNAME_RT}
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

        include(FindOpenCL)
        find_package(OpenCL REQUIRED)
        include_directories(${OPENCL_INCLUDE_DIR})
        target_link_libraries(RT ${GTK_LIBRARIES} OpenCL::OpenCL)
    else()
        message (FATAL_ERROR "Neither Intel nor NVIDIA nor AMD OpenCL SDK for Windows was found. Install one of those")
    endif()

endif()
