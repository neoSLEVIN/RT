/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 15:51:37 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/06 00:05:24 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ocl.h"

void	run_cl(t_ocl *ocl)
{
	int		err;

	err = clEnqueueNDRangeKernel(ocl->command_queue, ocl->kernel, 1, NULL,
		&ocl->work_size, &ocl->group_size, 0, NULL, NULL);
	check_error_cl(err, "clEnqueueNDRangeKernel", NULL);
	err = clEnqueueReadBuffer(ocl->command_queue, ocl->mem_obj[0], CL_FALSE, 0,
		ocl->work_size * sizeof(cl_int), ocl->mem[0], 0, NULL, NULL);
	check_error_cl(err, "clEnqueueReadBuffer", NULL);
	err = clFinish(ocl->command_queue);
	check_error_cl(err ,"clFinish", NULL);
}
