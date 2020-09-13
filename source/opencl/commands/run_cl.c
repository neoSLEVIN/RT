/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/16 06:37:20 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ocl.h"

void		run_cl(t_ocl *ocl)
{
	int	err;

	err = clEnqueueNDRangeKernel(ocl->queue, ocl->kernel, 1, NULL,
		&ocl->work_size, &ocl->group_size, 0, NULL, NULL);
	check_error_cl(err, "clEnqueueNDRangeKernel", NULL);
	err = clEnqueueReadBuffer(ocl->queue, ocl->dto.output_data, CL_FALSE, 0,
		ocl->work_size * sizeof(cl_uchar4), ocl->dto.buffer, 0, NULL, NULL);
	check_error_cl(err, "clEnqueueReadBuffer", NULL);
	err = clEnqueueReadBuffer(ocl->queue, ocl->dto.output_id, CL_FALSE, 0,
		sizeof(int), ocl->dto.shape_id, 0, NULL, NULL);
	check_error_cl(err, "clEnqueueReadBuffer", NULL);
	err = clFinish(ocl->queue);
	check_error_cl(err, "clFinish", NULL);
}
