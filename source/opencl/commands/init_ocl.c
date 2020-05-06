/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ocl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 13:07:11 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/06 01:48:16 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ocl.h"

void	init_ocl(t_ocl *ocl)
{
	ocl->platform = NULL;
	ocl->device_id = NULL;
	ocl->context = NULL;
	ocl->command_queue = NULL;
	ocl->kernel_size = 0;
	ocl->kernel_text = NULL;
	ocl->program = NULL;
	ocl->kernel = NULL;
	ocl->mem_obj[0] = NULL;
	ocl->mem_obj[1] = NULL;
	ocl->work_size = ROWS * COLS;
	ocl->group_size = GROUP_SIZE;
	ocl->mem[0] = NULL;
	ocl->mem[1] = NULL;
}
