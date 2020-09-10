#include "ocl.h"

void	update_anti_aliasing_arg(t_ocl *ocl)
{
	int	err;

	err = clSetKernelArg(ocl->kernel, 13, sizeof(int),
						ocl->dto.anti_aliasing);
	check_error_cl(err, "clSetKernelArg", "anti_aliasing");
}
