#include "gtk_module.h"

void	restart_position(t_rt *rt)
{
	if (!rt->info->r_key)
		return ;
	translate_cam(&rt->ocl->dto.cam, &rt->scene->cam);
	clear_shape_marker(rt);
	rt->info->update_cam = TRUE;
}
