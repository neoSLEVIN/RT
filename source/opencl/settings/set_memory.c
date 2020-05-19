/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_memory.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/09 15:30:54 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ocl.h"

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

void	set_memory_input(t_ocl *ocl, SCENE *scene)
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
	
	t_ppm_image *image = readPPM("/Users/dmitry/Desktop/__RT_material/ppm_ex/dan.ppm");
	int total_size = sizeof(unsigned char) * image->height * image->width * 3;
	ocl->dto.texture = clCreateBuffer(ocl->context, CL_MEM_READ_WRITE,
	total_size, NULL, &err);
	check_error_cl(err,"clCreateBuffer", "input_seeds");
	err = clEnqueueWriteBuffer(ocl->queue, ocl->dto.texture, CL_TRUE, 0,
		total_size, image->data, 0, NULL, NULL);
	check_error_cl(err,"clEnqueueWriteBuffer", NULL);
}
