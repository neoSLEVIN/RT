/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/29 20:40:52 by cschoen           #+#    #+#             */
/*   Updated: 2020/03/30 03:45:43 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

# include "ocl.h"

void	error(const int num, const char *str)
{
	ft_printf("Error number:\t%d\nError in:\t%s\n", num, str);
	exit (1);
}

void	init_ocl(t_ocl *ocl)
{
	ocl->ret_num_platforms = 0;
	ocl->ret_num_devices = 0;
	ocl->platform_id = NULL;
	ocl->device_id = NULL;
	ocl->context = NULL;
	ocl->command_queue = NULL;
	ocl->kernel_size = 0;
	ocl->kernel_text = NULL;
	ocl->program = NULL;
	ocl->kernel = NULL;
	ocl->mem_obj = NULL;
	ocl->mem_length = 0;
}

void	create_cl(t_ocl *ocl)
{
	int	ret;

	/* получить доступные платформы */
	ret = clGetPlatformIDs(1, &ocl->platform_id, &ocl->ret_num_platforms);
	ret ? error(ret, "clGetPlatformIDs") : 0;

	/* получить доступные устройства */
	ret = clGetDeviceIDs(ocl->platform_id, CL_DEVICE_TYPE_DEFAULT, 1,
						&ocl->device_id, &ocl->ret_num_devices);
	ret ? error(ret, "clGetDeviceIDs") : 0;

	/* создать контекст */
	ocl->context = clCreateContext(NULL, 1, &ocl->device_id, NULL, NULL, &ret);
	ret ? error(ret, "clCreateContext") : 0;

	/* создаем команду */
	ocl->command_queue =
			clCreateCommandQueueWithProperties(ocl->context, ocl->device_id,
											NULL, &ret);
	ret ? error(ret, "clCreateCommandQueueWithProperties") : 0;
}

void	compile_cl(t_ocl *ocl)
{
	int		fd;
	int		ret;
	size_t	source_size;

	if ((fd = open(KERNEL_PATH, O_RDONLY)) < 0)
		error(fd, "Can't open "KERNEL_PATH);
	if (!(ocl->kernel_text = ft_strnew(KERNEL_SIZE)))
		error(0, "Can't allocate memory for kernel_text");
	if ((source_size = read(fd, ocl->kernel_text, KERNEL_SIZE)) < 0)
		error(source_size, "Can't read "KERNEL_PATH);
	ocl->kernel_size += source_size;
	close(fd);

	/* создать бинарник из кода программы */
	ocl->program = clCreateProgramWithSource(ocl->context, 1,
		(const char **)&ocl->kernel_text, (const size_t *)&source_size, &ret);
	ret ? error(ret, "clCreateProgramWithSource") : 0;

	/* скомпилировать программу */
	ret = clBuildProgram(ocl->program, 1, &ocl->device_id, NULL, NULL, NULL);
	ret ? error(ret, "clBuildProgram") : 0;

	/* создать кернел */
	ocl->kernel = clCreateKernel(ocl->program, "test", &ret);
	ret ? error(ret, "clCreateKernel") : 0;
}

void	setting_cl(t_ocl *ocl)
{
	int	ret;

	ocl->mem_length = GLOBAL_WORK_SIZE;
	if (!(ocl->mem = (cl_int *)malloc(sizeof(cl_int) * ocl->mem_length)))
		error(0, "Can't allocate memory for mem");
	ft_bzero((void*)ocl->mem, ocl->mem_length);

	/* создать буфер */
	ocl->mem_obj = clCreateBuffer(ocl->context, CL_MEM_READ_WRITE,
								ocl->mem_length * sizeof(cl_int), NULL, &ret);
	ret ? error(ret, "clCreateBuffer") : 0;

	/* записать данные в буфер */
	ret = clEnqueueWriteBuffer(ocl->command_queue, ocl->mem_obj, CL_TRUE, 0,
					ocl->mem_length * sizeof(cl_int), ocl->mem, 0, NULL, NULL);
	ret ? error(ret, "clEnqueueWriteBuffer") : 0;

	/* устанавливаем параметр. 0 - позиция параметра в аргументах ф-ции */
	ret = clSetKernelArg(ocl->kernel, 0, sizeof(cl_mem), (void *)&ocl->mem_obj);
	ret ? error(ret, "clSetKernelArg") : 0;
}

void	run_cl(t_ocl *ocl)
{
	int		ret;
	size_t	global_work_size[1] = { GLOBAL_WORK_SIZE };

	/* выполнить кернел */
	ret = clEnqueueNDRangeKernel(ocl->command_queue, ocl->kernel, 1, NULL,
								global_work_size, NULL, 0, NULL, NULL);
	ret ? error(ret, "clEnqueueNDRangeKernel") : 0;

	/* считать данные из буфера */
	ret = clEnqueueReadBuffer(ocl->command_queue, ocl->mem_obj, CL_FALSE, 0,
					ocl->mem_length * sizeof(float), ocl->mem, 0, NULL, NULL);
	ret ? error(ret, "clEnqueueReadBuffer") : 0;
}
