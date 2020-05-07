/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_memory.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 21:17:03 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/07 01:25:47 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ocl.h"

void	set_memory_output(t_ocl *ocl)
{
	cl_int	err;

	ocl->dto.output_data = clCreateBuffer(ocl->context, CL_MEM_WRITE_ONLY,
		sizeof(cl_char4) * ocl->work_size, NULL, &err);
	check_error_cl(err,"clCreateBuffer", "output_data");
}

void	set_memory_input(t_ocl *ocl, t_scene *scene)
{
	cl_int	err;

	ocl->dto.input_shapes = clCreateBuffer(ocl->context,
		CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
		sizeof(DTO_SHAPE) * scene->s_cnt, ocl->dto.shapes, &err);
	check_error_cl(err,"clCreateBuffer", "input_shapes");
	ocl->dto.input_lights = clCreateBuffer(ocl->context,
		CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
		sizeof(DTO_LIGHT) * scene->l_cnt, ocl->dto.lights, &err);
	check_error_cl(err,"clCreateBuffer", "input_lights");
	//random
	// TODO refactor
	int i = 0;
	unsigned int *seeds =
		(unsigned int *)malloc(sizeof(unsigned int) * ocl->work_size);
	while (i < ocl->work_size) {
		int rand1 = rand();
		seeds[i] = rand1;
		if (seeds[i] < 2)
			seeds[i] = 2;
		i++;
	}
	ocl->dto.input_seeds = clCreateBuffer(ocl->context, CL_MEM_READ_WRITE,
		sizeof(unsigned int) * ocl->work_size, NULL, &err);
	check_error_cl(err,"clCreateBuffer", "input_seeds");
	err = clEnqueueWriteBuffer(ocl->queue, ocl->dto.input_seeds, CL_TRUE, 0,
		sizeof(unsigned int) * ocl->work_size, seeds, 0, NULL, NULL);
	check_error_cl(err,"clEnqueueWriteBuffer", NULL);
}