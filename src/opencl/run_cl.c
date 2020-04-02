/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 15:51:37 by cschoen           #+#    #+#             */
/*   Updated: 2020/04/02 01:02:34 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ocl.h"

void	run_cl(t_ocl *ocl)
{
	int		ret;
	size_t	global_work_size = GLOBAL_WORK_SIZE;

	ret = clEnqueueNDRangeKernel(ocl->command_queue, ocl->kernel, 1, NULL,
								&global_work_size, NULL, 0, NULL, NULL);
	check_error_cl(ret, "clEnqueueNDRangeKernel", NULL);
	ret = clEnqueueReadBuffer(ocl->command_queue, ocl->mem_obj[0], CL_TRUE, 0,
		ocl->mem_length * sizeof(cl_int), ocl->mem[0], 0, NULL, NULL);
	check_error_cl(ret, "clEnqueueReadBuffer", NULL);
}
