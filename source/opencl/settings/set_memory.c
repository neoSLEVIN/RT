/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_memory.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/28 20:00:47 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ocl.h"

void	set_memory_input_seeds(t_ocl *ocl)
{
	cl_int			err;
	int				i;
	unsigned int	*seeds;
	int				rand1;

	i = -1;
	seeds = (unsigned int *)malloc(sizeof(unsigned int) * ocl->work_size);
	if (!seeds)
		ft_error("Can't allocate memory");
	while (++i < ocl->work_size)
	{
		rand1 = rand();
		seeds[i] = rand1;
		if (seeds[i] < 2)
			seeds[i] = 2;
	}
	ocl->dto.input_seeds = clCreateBuffer(ocl->context, CL_MEM_READ_WRITE,
		sizeof(unsigned int) * ocl->work_size, NULL, &err);
	check_error_cl(err,"clCreateBuffer", "input_seeds");
	err = clEnqueueWriteBuffer(ocl->queue, ocl->dto.input_seeds, CL_TRUE, 0,
		sizeof(unsigned int) * ocl->work_size, seeds, 0, NULL, NULL);
	check_error_cl(err,"clEnqueueWriteBuffer", NULL);
}

void	set_memory_input(t_ocl *ocl, SCENE *scene)
{
	cl_int	err;
	int		alloc_size;

	alloc_size = (scene->s_cnt == 0) ? 1 : scene->s_cnt;
	ocl->dto.input_shapes = clCreateBuffer(ocl->context,
		CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
		sizeof(DTO_SHAPE) * alloc_size, ocl->dto.shapes, &err);
	check_error_cl(err,"clCreateBuffer", "input_shapes");
	ocl->dto.input_lights = clCreateBuffer(ocl->context,
		CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
		sizeof(DTO_LIGHT) * scene->l_cnt, ocl->dto.lights, &err);
	check_error_cl(err,"clCreateBuffer", "input_lights");
	alloc_size = (scene->t_cnt == 0) ? 1 : scene->t_cnt;
	ocl->dto.input_texture = clCreateBuffer(ocl->context, CL_MEM_READ_WRITE,
		sizeof(DTO_PPM_IMG) * alloc_size, NULL, &err);
	check_error_cl(err,"clCreateBuffer", "input_texture");
	if (ocl->dto.t_cnt > 0)
	{
		err = clEnqueueWriteBuffer(ocl->queue, ocl->dto.input_texture,
			CL_TRUE, 0, sizeof(DTO_PPM_IMG) * *ocl->dto.t_cnt,
			ocl->dto.textures, 0, NULL, NULL);
		check_error_cl(err,"clEnqueueWriteBuffer", "input_texture");
	}
}

void	set_memory_output(t_ocl *ocl)
{
	cl_int	err;

	ocl->dto.output_data = clCreateBuffer(ocl->context, CL_MEM_WRITE_ONLY,
		sizeof(cl_char4) * ocl->work_size, NULL, &err);
	check_error_cl(err,"clCreateBuffer", "output_data");
	ocl->dto.output_id = clCreateBuffer(ocl->context, CL_MEM_WRITE_ONLY,
		sizeof(int), NULL, &err);
	check_error_cl(err,"clCreateBuffer", "output_id");
}
