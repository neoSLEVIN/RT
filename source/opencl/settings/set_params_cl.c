/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_params_cl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 15:48:36 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/06 06:46:32 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ocl.h"

# define PI 3.14159265359f
#include <math.h>

void	translate_shapes(t_dto *dto, SHAPE *shape, int cnt)
{
	int	i;

	if (!(dto->shapes = (DTO_SHAPE*)malloc(sizeof(DTO_SHAPE) * cnt)))
		ft_error("Can't allocate memory");
	i = -1;
	while (++i < cnt && shape)
	{
		dto->shapes[i] = shape->dto;
		shape = shape->next;
	}
}

void	translate_lights(t_dto *dto, LIGHT *light, int cnt)
{
	int	i;

	if (!(dto->lights = (DTO_LIGHT*)malloc(sizeof(DTO_LIGHT) * cnt)))
		ft_error("Can't allocate memory");
	i = -1;
	while (++i < cnt && light)
	{
		dto->lights[i] = light->dto;
		light = light->next;
	}
}

void	set_memory_output(t_ocl *ocl)
{
	cl_int	err;

	ocl->dto.output_data = clCreateBuffer(ocl->context, CL_MEM_WRITE_ONLY,
		sizeof(cl_float3) * ocl->work_size, NULL, &err);
	check_error_cl(err,"clCreateBuffer", "output_data");
}

void	set_memory_input(t_ocl *ocl, t_scene *scene)
{
	cl_int	err;

//	ocl->dto.input_cam = clCreateBuffer(ocl->context, CL_MEM_READ_ONLY, sizeof(t_cam1), &cl->cam, &err);
//	check_error_cl(err,"clCreateBuffer", "input_cam");
	ocl->dto.input_shapes = clCreateBuffer(ocl->context,
		CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
		sizeof(DTO_SHAPE) * scene->s_cnt, ocl->dto.shapes, &err);
	check_error_cl(err,"clCreateBuffer", "input_shapes");
	ocl->dto.input_lights = clCreateBuffer(ocl->context,
		CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
		sizeof(DTO_LIGHT) * scene->l_cnt, ocl->dto.lights, &err);
	check_error_cl(err,"clCreateBuffer", "input_lights");
	//random
	int i = 0;
	unsigned int pixelCount = COLS * ROWS;
	unsigned int *seeds = (unsigned int *)malloc(sizeof(unsigned int) * pixelCount * 2);
	while (i < pixelCount * 2) {
		int rand1 = rand();
		seeds[i] = rand1;
		if (seeds[i] < 2)
			seeds[i] = 2;
		i++;
	}
	ocl->dto.input_seeds = clCreateBuffer(ocl->context, CL_MEM_READ_WRITE,
		sizeof(unsigned int) * ROWS * COLS * 2, NULL, &err);
	check_error_cl(err,"clCreateBuffer", "input_seeds");
	err = clEnqueueWriteBuffer(ocl->queue, ocl->dto.input_seeds, CL_TRUE, 0,
		sizeof(unsigned int) * ROWS * COLS * 2, seeds, 0, NULL, NULL);
	check_error_cl(err,"clEnqueueWriteBuffer", NULL);
}

void	set_kernel_args(cl_kernel kernel, t_dto *dto, t_scene *scene)
{
	cl_int	err;

	err = clSetKernelArg(kernel, 0, sizeof(cl_mem), &(dto->input_shapes));
	check_error_cl(err,"clSetKernelArg", "input_shapes");
	err = clSetKernelArg(kernel, 1, sizeof(int), &(scene->s_cnt));
	check_error_cl(err,"clSetKernelArg", "s_cnt");
	err = clSetKernelArg(kernel, 2, sizeof(cl_mem), &(dto->input_lights));
	check_error_cl(err,"clSetKernelArg", "input_lights");
	err = clSetKernelArg(kernel, 3, sizeof(int), &(scene->l_cnt));
	check_error_cl(err,"clSetKernelArg", "l_cnt");
	err = clSetKernelArg(kernel, 4, sizeof(t_cam), &(scene->cam));
	check_error_cl(err,"clSetKernelArg", "cam");
	err = clSetKernelArg(kernel, 5, sizeof(cl_mem), &(dto->output_data));
	check_error_cl(err,"clSetKernelArg", "output_data");
	err = clSetKernelArg(kernel, 6, sizeof(cl_mem), &(dto->input_seeds));
	check_error_cl(err,"clSetKernelArg", "input_seeds");
}

// TODO MOVE THIS FUNC TO ANOTHER PLACE
cl_float	v3_length(FLT3 v)
{
	return ((cl_float)sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

FLT3	v3_scale(FLT3 v, cl_float scale)
{
	v.x *= scale;
	v.y *= scale;
	v.z *= scale;
	return (v);
}

FLT3	v3_norm(FLT3 v)
{
	cl_float len = v3_length(v);
	if (len > 0)
		return (v3_scale(v, 1.0 / len));
	return (cl_float3){0,0,0};
}

FLT3	v3_cross(FLT3 v1, FLT3 v2)
{
	FLT3	new_v;

	new_v.x = v1.y * v2.z - v1.z * v2.y;
	new_v.y = v1.z * v2.x - v1.x * v2.z;
	new_v.z = v1.x * v2.y - v1.y * v2.x;
	return (new_v);
}

static void	init_camera(t_cam *cam)
{
	cl_float	fov;
	cl_float	ratio;
	FLT3		upguide;
	// TODO CHANGE MAGIC NUMBERS
	cam->screen_h = ROWS;
	cam->screen_w = COLS;
	fov = 25.0f * PI / 180;
	ratio = (float)cam->screen_w / (float)cam->screen_h;
	upguide = (FLT3){0.0f, 1.0f, 0.0f};
	cam->origin = cam->transform.position;
	cam->target = cam->transform.direction;
	cam->forward = (FLT3){cam->target.x - cam->origin.x,
						  cam->target.y - cam->origin.y,
						  cam->target.z - cam->origin.z};
	cam->forward = v3_norm(cam->forward);
	cam->right = v3_cross(cam->forward, upguide);
	if (v3_length(cam->right) < 0.0000001f)
		cam->right = v3_cross(cam->forward, (FLT3){1.0f, 0.0f, 0.0f});
	cam->right = v3_norm(cam->right);
	cam->up = v3_cross(cam->right, cam->forward);
	cam->viewport_h = tan(fov) / 2;
	cam->viewport_w = cam->viewport_h * ratio;
	cam->upguide = upguide;
}

void	set_params_cl(t_ocl *ocl, t_scene *scene)
{
	init_camera(&scene->cam);
	translate_shapes(&ocl->dto, scene->shapes, scene->s_cnt);
	translate_lights(&ocl->dto, scene->lights, scene->l_cnt);
	set_memory_output(ocl);
	set_memory_input(ocl, scene);
	set_kernel_args(ocl->kernel, &ocl->dto, scene);
}
