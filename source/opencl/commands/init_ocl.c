/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ocl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 13:07:11 by cschoen           #+#    #+#             */
/*   Updated: 2020/04/02 01:09:04 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ocl.h"

void	init_ocl(t_ocl *ocl)
{
	int	i;

	i = -1;
	ocl->device_id = NULL;
	ocl->context = NULL;
	ocl->command_queue = NULL;
	while (++i < KERNEL_FILE_CNT)
	{
		ocl->kernel_size[i] = 0;
		ocl->kernel_text[i] = NULL;
	}
	ocl->program = NULL;
	ocl->kernel = NULL;
	ocl->mem_obj[0] = NULL;
	ocl->mem_obj[1] = NULL;
	ocl->mem_length = 0;
	ocl->mem[0] = NULL;
	ocl->mem[1] = NULL;
}
