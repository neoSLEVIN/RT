#include "gtk_module.h"

void	blur_scale_moved(GtkRange *range, gpointer data)
{
	t_rt	*rt;

	rt = (t_rt*)data;
	rt->scene->filter_params.x = gtk_range_get_value(range);
	update_filter_params(rt->ocl);
	rt->info->update = TRUE;
}

void	sepia_scale_moved(GtkRange *range, gpointer data)
{
	t_rt	*rt;

	rt = (t_rt*)data;
	rt->scene->filter_params.y = gtk_range_get_value(range);
	update_filter_params(rt->ocl);
	rt->info->update = TRUE;
}

void	noise_scale_moved(GtkRange *range, gpointer data)
{
	t_rt	*rt;

	rt = (t_rt*)data;
	rt->scene->filter_params.z = gtk_range_get_value(range);
	update_filter_params(rt->ocl);
	rt->info->update = TRUE;
}