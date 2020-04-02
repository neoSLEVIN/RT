/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_params_cl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 15:48:36 by cschoen           #+#    #+#             */
/*   Updated: 2020/04/02 04:59:18 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ocl.h"
#include "libft.h"

void	make_buffer(t_ocl *ocl)
{
	int	i;
	int	ret;
	int	*arr;

	ret = 0;
	i = -1;
	if (!(ocl->mem[0] = (cl_int *)malloc(sizeof(cl_int) * ocl->mem_length)))
		check_error_cl(1, "Can't allocate memory for mem", NULL);
	ft_bzero(ocl->mem[0], sizeof(cl_int) * ocl->mem_length);
	if (!(ocl->mem[1] = (cl_int *)malloc(sizeof(cl_int) * ocl->mem_length)))
		check_error_cl(1, "Can't allocate memory for mem", NULL);
	while (++i < ocl->mem_length)
		ocl->mem[1][i] = (cl_int)i;
	i = -1;
	if (!(arr = (int*)malloc(sizeof(int) * ocl->mem_length)))
		check_error_cl(1, "Can't allocate memory for arr", NULL);
	while (++i < ocl->mem_length)
		arr[i] = i;
	ocl->mem_obj[0] = clCreateBuffer(ocl->context, CL_MEM_WRITE_ONLY,
									 sizeof(cl_int) * ocl->mem_length, NULL, &ret);
	check_error_cl(ret, "clCreateBuffer", "ocl->mem_obj[0]");
	ocl->mem_obj[1] = clCreateBuffer(ocl->context,
		CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
		sizeof(cl_int) * ocl->mem_length, arr, &ret);
	check_error_cl(ret, "clCreateBuffer", "ocl->mem_obj[1]");
}

void	set_params_cl(t_ocl *ocl)
{
	int	ret;

	ocl->mem_length = GLOBAL_WORK_SIZE;
	make_buffer(ocl);
	ret = clSetKernelArg(ocl->kernel, 0, sizeof(cl_mem), &ocl->mem_obj[0]);
	check_error_cl(ret, "clSetKernelArg", "&ocl->mem_obj[0]");
	ret = clSetKernelArg(ocl->kernel, 1, sizeof(cl_mem), &ocl->mem_obj[1]);
	check_error_cl(ret, "clSetKernelArg", "&ocl->mem_obj[1]");
}
