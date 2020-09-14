/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/29 00:01:13 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OCL_H
# define OCL_H

# include "libft.h"
# include "info.h"

# ifdef __APPLE__
#  define BUILD_OPTIONS_CL "-cl-std=CL1.0 -cl-mad-enable"
#  define CREATE_QUEUE_FUNC clCreateCommandQueue
#  define CREATE_QUEUE_PARAM 0
#  define IS_APPLE TRUE
# else
#  define BUILD_OPTIONS_CL NULL
#  define CREATE_QUEUE_FUNC clCreateCommandQueueWithProperties
#  define CREATE_QUEUE_PARAM NULL
#  define IS_APPLE FALSE
# endif

# define GROUP_SIZE 64

/*
** =============================================================================
** ======================== Adding absolute kernel path ========================
** =============================================================================
*/
# define KERNEL_PATH PROJ_DIR"kernel/"

/*
** =============================================================================
** =========================== Listing Kernel files ============================
** =============================================================================
*/
# define KERNEL_FILE_SIZE 13000
# define KERNEL_FILE_CNT 17

static char				*g_kernel_file_arr[KERNEL_FILE_CNT] = {
	KERNEL_PATH"include.cl",
	KERNEL_PATH"normals.cl",
	KERNEL_PATH"sections.cl",
	KERNEL_PATH"semi_intersections.cl",
	KERNEL_PATH"intersections.cl",
	KERNEL_PATH"intersections2.cl",
	KERNEL_PATH"light.cl",
	KERNEL_PATH"random.cl",
	KERNEL_PATH"reflect.cl",
	KERNEL_PATH"refract.cl",
	KERNEL_PATH"color.cl",
	KERNEL_PATH"ray.cl",
	KERNEL_PATH"ray_tracing.cl",
	KERNEL_PATH"uv_mapping.cl",
	KERNEL_PATH"uv_patterns.cl",
	KERNEL_PATH"perlin_noise.cl",
	KERNEL_PATH"filters.cl"
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
	DTO_PPM_IMG			*textures;
	DTO_PPM_IMG			*normal_maps;
	DTO_SHAPE			*shapes;
	DTO_LIGHT			*lights;
	FLT3				*points;
	FLT3				*colors;
	cl_int3				*faces;
	int					*s_cnt;
	int					*l_cnt;
	int					*t_cnt;
	int					*n_cnt;
	int					*p_cnt;
	int					*f_cnt;
	INT2				*cursor;
	FLT3				*filter_params;
	cl_mem				input_shapes;
	cl_mem				input_lights;
	cl_mem				input_seeds;
	cl_mem				input_points;
	cl_mem				input_faces;
	cl_mem				input_colors;
	cl_mem				input_texture;
	cl_mem				input_normal_maps;
	cl_mem				output_data;
	cl_mem				output_id;
	cl_uchar4			*buffer;
	int					*shape_id;
	int					*anti_aliasing;
	int					*mirror;
	FILTER				*filter;
	cl_uchar4			*filter_buff;
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
void					translate_off(t_dto *dto, t_off *off);
void					translate_cam(DTO_CAM *dto, CAMERA *cam);
void					translate_textures(DTO_PPM_IMG **dto, PPM_IMG *texture,
								int cnt);
void					translate_shapes(DTO_SHAPE **dto, SHAPE *shape,
								int cnt);
void					translate_lights(DTO_LIGHT **dto, LIGHT *light,
								int cnt);
/*
** ============= First creating of all buffers from DTO for OpenCL =============
*/
void					set_memory_output(t_ocl *ocl);
void					set_memory_input(t_ocl *ocl, SCENE *scene);
void					set_memory_input_seeds(t_ocl *ocl);
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
void					realloc_ppm_img_dto(DTO_PPM_IMG **dto, PPM_IMG *ppm_img,
								int cnt);
/*
** ====================== Update arguments for the kernel ======================
*/
void					update_cursor_arg(t_ocl *ocl);
void					update_filter_params(t_ocl *ocl);
void					update_anti_aliasing_arg(t_ocl *ocl);
void					update_mirror_arg(t_ocl *ocl);
void					update_cam_arg(t_ocl *ocl, _Bool *update_flag);
void					update_shapes_arg(t_ocl *ocl, _Bool *update_size,
								_Bool *update_shapes);
void					update_lights_arg(t_ocl *ocl, _Bool *update_size,
								_Bool *update_lights);
void					update_off_points_arg(t_ocl *ocl,
								_Bool *update_points);
void					update_textures_arg(t_ocl *ocl, int cnt);
void					update_normal_maps_arg(t_ocl *ocl, int cnt);
/*
** =============================================================================
** =================================== Utils ===================================
** =============================================================================
*/
void					new_ocl(t_ocl **ocl);
void					init_dto_cam(DTO_CAM *cam, cl_float fov, INT2 screen);
void					check_error_cl(const int num, const char *message,
								char *path);
DTO_PPM_IMG				*read_ppm(const char *filename);
_Bool					read_ppm_safe(const char *filename, DTO_PPM_IMG **dto,
								char **err);
_Bool					ppm_error_safe(char **err, const char *text,
								DTO_PPM_IMG **dto);

#endif
