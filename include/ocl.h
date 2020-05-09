/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/09 19:26:49 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OCL_H
# define OCL_H

# include "libft.h"
# include "scene.h"

# ifdef __APPLE__
#  define BUILD_OPTIONS_CL "-cl-std=CL1.0 -cl-mad-enable"
#  define CREATE_QUEUE(ctxt, dev, prop, err) \
	clCreateCommandQueue(ctxt, dev, prop, err)
# else
#  define BUILD_OPTIONS_CL NULL
#  define CREATE_QUEUE(ctxt, dev, prop, err) \
	clCreateCommandQueueWithProperties(ctxt, dev, prop, err)
# endif

/*
** =============================================================================
** ============================= IMAGE resolution ==============================
** =================== You can add your favorite resolution: ===================
** # elif GTK_IMAGE_SIZE == (X)
** #  define COLS (WIDTH)
** #  define ROWS (HEIGHT)
** #  define FPS (FRAME_PER_SECOND)
** =============================================================================
*/
# define GTK_IMAGE_SIZE 2
# if GTK_IMAGE_SIZE == 1
#  define COLS 1280
#  define ROWS 1024
#  define FPS 1.22
# elif GTK_IMAGE_SIZE == 2
#  define COLS 1440
#  define ROWS 960
#  define FPS 1.16
# elif GTK_IMAGE_SIZE == 3
#  define COLS 1024
#  define ROWS 768
#  define FPS 2.04
# elif GTK_IMAGE_SIZE == 4
#  define COLS 800
#  define ROWS 600
#  define FPS 3.33
# elif GTK_IMAGE_SIZE == 5
#  define COLS 640
#  define ROWS 480
#  define FPS 5.2
# else
#  define COLS 320
#  define ROWS 200
#  define FPS 25
# endif

# define GROUP_SIZE 64
/*
** =============================================================================
** =================== Adding absolute path for xcode users ====================
** =============================================================================
*/
// TODO fix that when delete CMake
# if __APPLE__
#  define AUTHOR 1
#  if AUTHOR == 1
#   define ABSOLUTE_PATH "bla_bla_bla/path/to/Dima's_project/dir/kernel/"
#  else
#   define ABSOLUTE_PATH "bla_bla_bla/path/to/Kostya's_project/dir/kernel/"
#  endif
# else
#  define ABSOLUTE_PATH "kernel/"
# endif

/*
** =============================================================================
** =========================== Listing Kernel files ============================
** =============================================================================
*/
# define KERNEL_FILE_SIZE 26000
# define KERNEL_FILE_CNT 1
static char	*g_kernel_file_arr[KERNEL_FILE_CNT] = {
		ABSOLUTE_PATH"ray_tracing.cl"
};
/*
** TODO !!! Don't forget to add the path of the kernel file in CMakeList !!!
*/

/*
** =============================================================================
** ======================== Camera Data Transfer Object ========================
** ========================= Set as a kernel argument ==========================
** =============================================================================
*/
# define DTO_CAM struct s_dto_cam
struct					s_dto_cam
{
	int					screen_w;
	int					screen_h;
	cl_float			viewport_h;
	cl_float			viewport_w;
	FLT3				origin;
	FLT3				target;
	FLT3				forward;
	FLT3				up;
	FLT3				right;
	FLT3				upguide;
};

/*
** =============================================================================
** ============================ Main Entity for DTO ============================
** ==================== Contains arguments for the kernel ======================
** =============================================================================
*/
typedef struct			s_dto
{
	DTO_CAM				cam;
	DTO_SHAPE			*shapes;
	DTO_LIGHT			*lights;
	int					*s_cnt;
	int					*l_cnt;
	cl_mem				input_shapes;
	cl_mem				input_lights;
	cl_mem				input_seeds;
	cl_mem				output_data;
	cl_char4			*buffer;
}						t_dto;

/*
** =============================================================================
** =========================== Main Entity for OpenCL ==========================
** ================ Contains info about Program, devices, etc ==================
** ======================= Also contains entity for DTOs =======================
** =============================================================================
*/
typedef struct			s_opencl
{
	cl_platform_id		platform;
	cl_device_id		device;
	cl_context			context;
	cl_command_queue	queue;
	char				*kernel_text;
	size_t				kernel_size;
	size_t				work_size;
	size_t				group_size;
	cl_program			program;
	cl_kernel			kernel;
	t_dto				dto;
}						t_ocl;

/*
** ================================= Commands ==================================
*/
void					init_ocl(t_ocl *ocl);
void					create_cl(t_ocl *ocl);
void					compile_cl(t_ocl *ocl);
void					setting_cl(t_ocl *ocl, SCENE *scene);
void					run_cl(t_ocl *ocl);
/*
** ================================= Settings ==================================
*/
void					translate_cam(DTO_CAM *dto, CAMERA *cam);
void					translate_shapes(DTO_SHAPE **dto, SHAPE *shape,
								int cnt);
void					translate_lights(DTO_LIGHT **dto, LIGHT *light,
								int cnt);
void					set_memory_output(t_ocl *ocl);
void					set_memory_input(t_ocl *ocl, SCENE *scene);
void					set_kernel_args(cl_kernel kernel, t_dto *dto);
/*
** =================================== Utils ===================================
*/
void					new_ocl(t_ocl **ocl);
void					check_error_cl(const int num, const char *message,
								char *path);

#endif
