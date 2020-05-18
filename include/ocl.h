/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/17 03:38:07 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OCL_H
# define OCL_H

# include "libft.h"
# include "info.h"

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
# define GTK_IMAGE_SIZE 3
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
# elif GTK_IMAGE_SIZE == 5
#  define COLS 640
#  define ROWS 480
# else
#  define COLS 320
#  define ROWS 200
# endif

# define GROUP_SIZE 64

/*
** =============================================================================
** =================== Adding absolute path for xcode users ====================
** =============================================================================
*/
// TODO fix that when delete CMake
# if __APPLE__
#  define ABSOLUTE_PATH PROJECT_DIR
# else
#  define ABSOLUTE_PATH "kernel/"
# endif

/*
** =============================================================================
** =========================== Listing Kernel files ============================
** =============================================================================
*/
# define KERNEL_FILE_SIZE 13000
# define KERNEL_FILE_CNT 13
static char	*g_kernel_file_arr[KERNEL_FILE_CNT] = {
		ABSOLUTE_PATH"include.cl",
		ABSOLUTE_PATH"normals.cl",
		ABSOLUTE_PATH"intersections.cl",
		ABSOLUTE_PATH"light.cl",
		ABSOLUTE_PATH"random.cl",
		ABSOLUTE_PATH"reflect.cl",
		ABSOLUTE_PATH"refract.cl",
		ABSOLUTE_PATH"color.cl",
		ABSOLUTE_PATH"ray.cl",
		ABSOLUTE_PATH"ray_tracing.cl",
		ABSOLUTE_PATH"uv_mapping.cl",
		ABSOLUTE_PATH"uv_patterns.cl",
		ABSOLUTE_PATH"perlin_noise.cl"
};

/*
** =============================================================================
** ============================ Main Entity for DTO ============================
** =========== Contains DTO/output data and arguments for the kernel ===========
** =============================================================================
*/
typedef struct			s_dto
{
	DTO_CAM				cam;
	DTO_SHAPE			*shapes;
	DTO_LIGHT			*lights;
	int					*s_cnt;
	int					*l_cnt;
	INT2				*cursor;
	cl_mem				input_shapes;
	cl_mem				input_lights;
	cl_mem				input_seeds;
	cl_mem				output_data;
	cl_mem				output_id;
	cl_char4			*buffer;
	int					*shape_id;
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
** =============================================================================
** ================================= Commands ==================================
** =============================================================================
*/
void					init_ocl(t_ocl *ocl);
void					create_cl(t_ocl *ocl);
void					compile_cl(t_ocl *ocl);
void					setting_cl(t_ocl *ocl, SCENE *scene, t_info *info);
void					run_cl(t_ocl *ocl);
/*
** =============================================================================
** ================================= Settings ==================================
** =============================================================================
*/
/*
** ===================== Translate from parsed data to DTO =====================
*/
void					translate_cam(DTO_CAM *dto, CAMERA *cam);
void					translate_shapes(DTO_SHAPE **dto, SHAPE *shape,
								int cnt);
void					translate_lights(DTO_LIGHT **dto, LIGHT *light,
								int cnt);
/*
** ============= First creating of all buffers from DTO for OpenCL =============
*/
void					set_memory_output(t_ocl *ocl);
void					set_memory_input(t_ocl *ocl, SCENE *scene);
/*
** ================= First setting of all arguments to kernel ==================
*/
void					set_kernel_args(cl_kernel kernel, t_dto *dto);
/*
** =========== Update DTO arrays for new size (Reallocating memory) ============
*/
void					realloc_shapes_dto(DTO_SHAPE **dto, SHAPE *shape,
								int cnt);
void					realloc_lights_dto(DTO_LIGHT **dto, LIGHT *light,
								int cnt);
/*
** ====================== Update arguments for the kernel ======================
*/
void					update_cursor_arg(t_ocl *ocl);
void					update_cam_arg(t_ocl *ocl, _Bool *update_flag);
void					update_shapes_arg(t_ocl *ocl, _Bool *update_size,
								_Bool *update_shapes);
/*
** =============================================================================
** =================================== Utils ===================================
** =============================================================================
*/
void					new_ocl(t_ocl **ocl);
void					check_error_cl(const int num, const char *message,
								char *path);

#endif
