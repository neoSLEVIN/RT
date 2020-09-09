/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_ppm_img_args.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:30:36 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:30:37 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ocl.h"

void	update_textures_arg(t_ocl *ocl, int cnt)
{
	int	err;
	int	alloc_size;

	clReleaseMemObject(ocl->dto.input_texture);
	alloc_size = (cnt == 0) ? 1 : cnt;
	ocl->dto.input_texture = clCreateBuffer(ocl->context, CL_MEM_READ_WRITE,
		sizeof(DTO_PPM_IMG) * alloc_size, NULL, &err);
	check_error_cl(err, "clCreateBuffer", "input_texture");
	if (cnt > 0)
	{
		err = clEnqueueWriteBuffer(ocl->queue, ocl->dto.input_texture,
			CL_TRUE, 0, sizeof(DTO_PPM_IMG) * cnt,
			ocl->dto.textures, 0, NULL, NULL);
		check_error_cl(err, "clEnqueueWriteBuffer", "input_texture");
	}
	err = clSetKernelArg(ocl->kernel, 8, sizeof(cl_mem),
						&ocl->dto.input_texture);
	check_error_cl(err, "clSetKernelArg", "input_texture");
}

void	update_normal_maps_arg(t_ocl *ocl, int cnt)
{
	int	err;
	int	alloc_size;

	clReleaseMemObject(ocl->dto.input_normal_maps);
	alloc_size = (cnt == 0) ? 1 : cnt;
	ocl->dto.input_normal_maps = clCreateBuffer(ocl->context, CL_MEM_READ_WRITE,
		sizeof(DTO_PPM_IMG) * alloc_size, NULL, &err);
	check_error_cl(err, "clCreateBuffer", "input_normal_maps");
	if (cnt > 0)
	{
		err = clEnqueueWriteBuffer(ocl->queue, ocl->dto.input_normal_maps,
			CL_TRUE, 0, sizeof(DTO_PPM_IMG) * cnt,
			ocl->dto.normal_maps, 0, NULL, NULL);
		check_error_cl(err, "clEnqueueWriteBuffer", "input_normal_maps");
	}
	err = clSetKernelArg(ocl->kernel, 9, sizeof(cl_mem),
						&ocl->dto.input_normal_maps);
	check_error_cl(err, "clSetKernelArg", "input_normal_maps");
}
