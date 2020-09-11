#include "ocl.h"

void	update_anti_aliasing_arg(t_ocl *ocl)
{
	int	err;

	err = clSetKernelArg(ocl->kernel, 13, sizeof(int),
						ocl->dto.anti_aliasing);
	check_error_cl(err, "clSetKernelArg", "anti_aliasing");
}

void	update_mirror_arg(t_ocl *ocl)
{
	int	err;
	int	mirror;

	mirror = (IS_APPLE) ? 1 : *ocl->dto.mirror;
	err = clSetKernelArg(ocl->kernel, 14, sizeof(int),
						&mirror);
	check_error_cl(err, "clSetKernelArg", "mirror");
}
