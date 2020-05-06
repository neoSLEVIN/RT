/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/29 17:43:40 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/06 23:16:32 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef OCL_H
# define OCL_H

# include "libft.h"
# include "scene.h"

# ifdef __APPLE__
# define BUILD_OPTIONS_CL "-cl-std=CL1.0 -cl-mad-enable"
# else
# define BUILD_OPTIONS_CL NULL
# endif

/*
** =============================================================================
** ============================= IMAGE resolution ==============================
** =================== You can add your favorite resolution: ===================
** # elif GTK_IMAGE_SIZE == (X)
** #  define COLS (WIDTH)
** #  define ROWS (HEIGHT)
** =============================================================================
*/
# define GTK_IMAGE_SIZE 4
# if GTK_IMAGE_SIZE == 1
#  define COLS 1280
#  define ROWS 1024
# elif GTK_IMAGE_SIZE == 2
#  define COLS 1440
#  define ROWS 960
# elif GTK_IMAGE_SIZE == 3
#  define COLS 1024
#  define ROWS 768
# elif GTK_IMAGE_SIZE == 4
#  define COLS 800
#  define ROWS 600
# else
#  define COLS 640
#  define ROWS 480
# endif

# define BYTES_PER_PIXEL 3
# define GROUP_SIZE 64

/*
** =============================================================================
** =========================== Listing Kernel files ============================
** =============================================================================
*/
# define KERNEL_FILE_SIZE 13000
# define KERNEL_FILE_CNT 1
static char	*g_kernel_file_arr[KERNEL_FILE_CNT] = {
		"kernel/ray_tracing.cl"
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
	cl_float3			*buffer;
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
void					setting_cl(t_ocl *ocl, t_scene *scene);
void					run_cl(t_ocl *ocl);
/*
** ================================= Settings ==================================
*/
void					translate_cam(DTO_CAM *dto, t_cam *cam);
void					translate_shapes(DTO_SHAPE **dto, SHAPE *shape,
								int cnt);
void					translate_lights(DTO_LIGHT **dto, LIGHT *light,
								int cnt);
void					set_memory_output(t_ocl *ocl);
void					set_memory_input(t_ocl *ocl, t_scene *scene);
void					set_kernel_args(cl_kernel kernel, t_dto *dto);
/*
** =================================== Utils ===================================
*/
t_ocl					*new_ocl(void);
void					check_error_cl(const int num, const char *message,
								char *path);

#endif
