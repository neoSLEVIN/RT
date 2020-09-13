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

static void	particle_run_cl(t_ocl *ocl)
{
	int		err;
	int		i;
	size_t	offset;
	size_t	work_size;

	i = -1;
	while (++i < 100)
	{
		offset = ocl->work_size / 100 * i;
		work_size = ocl->work_size / 100;
		if (i == 9)
			work_size = ocl->work_size - (ocl->work_size / 100 * 99);
		err = clEnqueueNDRangeKernel(ocl->queue, ocl->kernel, 1, &offset,
			&work_size, &ocl->group_size, 0, NULL, NULL);
		check_error_cl(err, "clEnqueueNDRangeKernel", NULL);
	}
}

void		run_cl(t_ocl *ocl)
{
	int	err;

	if (IS_APPLE)
		particle_run_cl(ocl);
	else
	{
		err = clEnqueueNDRangeKernel(ocl->queue, ocl->kernel, 1, NULL,
			&ocl->work_size, &ocl->group_size, 0, NULL, NULL);
		check_error_cl(err, "clEnqueueNDRangeKernel", NULL);
	}
	err = clEnqueueReadBuffer(ocl->queue, ocl->dto.output_data, CL_FALSE, 0,
		ocl->work_size * sizeof(cl_uchar4), ocl->dto.buffer, 0, NULL, NULL);
	check_error_cl(err, "clEnqueueReadBuffer", NULL);
	err = clEnqueueReadBuffer(ocl->queue, ocl->dto.output_id, CL_FALSE, 0,
		sizeof(int), ocl->dto.shape_id, 0, NULL, NULL);
	check_error_cl(err, "clEnqueueReadBuffer", NULL);
	err = clFinish(ocl->queue);
	check_error_cl(err, "clFinish", NULL);
}
