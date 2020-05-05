/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 15:51:37 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/05 00:53:50 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ocl.h"

void	run_cl(t_ocl *ocl)
{
	int	ret;

	ret = clEnqueueNDRangeKernel(ocl->command_queue, ocl->kernel, 1, NULL,
								&ocl->mem_length, NULL, 0, NULL, NULL);
	check_error_cl(ret, "clEnqueueNDRangeKernel", NULL);
	ret = clEnqueueReadBuffer(ocl->command_queue, ocl->mem_obj[0], CL_TRUE, 0,
		ocl->mem_length * sizeof(cl_int), ocl->mem[0], 0, NULL, NULL);
	check_error_cl(ret, "clEnqueueReadBuffer", NULL);
}
