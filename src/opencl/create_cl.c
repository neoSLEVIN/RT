/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 13:08:41 by cschoen           #+#    #+#             */
/*   Updated: 2020/04/02 02:11:33 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ocl.h"

void	create_cl(t_ocl *ocl)
{
	int				ret;
	cl_uint			ret_num;
	cl_platform_id	platform_id;

	ret_num = 0;
	ret = clGetPlatformIDs(1, &platform_id, &ret_num);
	check_error_cl(ret, "clGetPlatformIDs", NULL);
	ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_DEFAULT, 1,
						&ocl->device_id, &ret_num);
	check_error_cl(ret, "clGetDeviceIDs", NULL);
	ocl->context = clCreateContext(NULL, 1, &ocl->device_id, NULL, NULL, &ret);
	check_error_cl(ret, "clCreateContext", NULL);
	ocl->command_queue = clCreateCommandQueueWithProperties(ocl->context,
												ocl->device_id, NULL, &ret);
	check_error_cl(ret, "clCreateCommandQueueWithProperties", NULL);
}
