/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/10 04:29:43 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ocl.h"

static void	get_platform_info(cl_platform_id *platforms, int cnt,
							cl_platform_id *checked_platform)
{
	cl_int	err;
	char	str[200];

	ft_bzero(&str, 200);
	while (cnt--)
	{
		err = clGetPlatformInfo(platforms[cnt], CL_PLATFORM_NAME,
								sizeof(str), str, NULL);
		check_error_cl(err, "Can't get platform name", NULL);
		ft_printf("\t%{}-17s%s\n", FT_CYAN, "Platform name:", str);
		if (ft_strnequ(str, "NVIDIA", 6))
			*checked_platform = platforms[cnt];
		ft_strclr(str);
		err = clGetPlatformInfo(platforms[cnt], CL_PLATFORM_VENDOR,
								sizeof(str), str, NULL);
		check_error_cl(err, "Can't get platform vendor", NULL);
		ft_printf("\t%{}-17s%s\n", FT_CYAN, "Platform vendor:", str);
		ft_strclr(str);
	}
}

static void	get_device_info(cl_device_id *device, int cnt)
{
	char	*str;
	size_t	size_str;
	cl_int	err;

	while (cnt--)
	{
		err = clGetDeviceInfo(device[cnt], CL_DEVICE_NAME, 1, NULL, &size_str);
		if (err != CL_SUCCESS)
		{
			ft_printf("%{}s\n", FT_PURPLE, "Can't get size name device");
			continue ;
		}
		if (!(str = (char*)malloc(size_str)))
			ft_error("Can't allocate memory");
		err = clGetDeviceInfo(device[cnt], CL_DEVICE_NAME, size_str, str, NULL);
		check_error_cl(err, "Can't get device name", NULL);
		ft_printf("\t%{}-17s%s\n", FT_CYAN, "Device name:", str);
		ft_strdel(&str);
	}
}

static void	get_platform(t_ocl *ocl)
{
	int				err;
	cl_uint			cnt;
	cl_platform_id	*platforms;

	cnt = 0;
	err = clGetPlatformIDs(1, &ocl->platform, &cnt);
	check_error_cl(err, "clGetPlatformIDs", NULL);
	platforms = (cl_platform_id*)malloc(sizeof(cl_platform_id) * cnt);
	if (!platforms)
		ft_error("Can't allocate memory");
	err = clGetPlatformIDs(cnt, platforms, NULL);
	check_error_cl(err, "clGetPlatformIDs", NULL);
	get_platform_info(platforms, cnt, &ocl->platform);
	ft_memdel((void**)&platforms);
}

static void	get_device(t_ocl *ocl)
{
	int				err;
	cl_uint			cnt;
	cl_device_id	*devices;

	cnt = 0;
	err = clGetDeviceIDs(ocl->platform, CL_DEVICE_TYPE_DEFAULT,
						1, &ocl->device, &cnt);
	check_error_cl(err, "clGetDeviceIDs", NULL);
	devices = (cl_device_id*)malloc(sizeof(cl_device_id) * cnt);
	if (!devices)
		ft_error("Can't allocate memory");
	err = clGetDeviceIDs(ocl->platform, CL_DEVICE_TYPE_DEFAULT,
			cnt, devices, NULL);
	check_error_cl(err, "clGetDeviceIDs", NULL);
	get_device_info(devices, cnt);
	ft_memdel((void**)&devices);
}

void		create_cl(t_ocl *ocl)
{
	int	err;

	get_platform(ocl);
	get_device(ocl);
	ocl->context = clCreateContext(NULL, 1, &ocl->device, NULL, NULL, &err);
	check_error_cl(err, "clCreateContext", NULL);
	ocl->queue =
		CREATE_QUEUE_FUNC(ocl->context, ocl->device, CREATE_QUEUE_PARAM, &err);
	check_error_cl(err, "CREATE_QUEUE_FUNC", NULL);
}
