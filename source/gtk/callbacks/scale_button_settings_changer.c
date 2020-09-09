#include "gtk_module.h"

void	step_scale_moved(GtkRange *range, gpointer data)
{
	t_rt	*rt;

	rt = (t_rt*)data;
	rt->scene->step = gtk_range_get_value(range);
}

void	angle_scale_moved(GtkRange *range, gpointer data)
{
	t_rt	*rt;

	rt = (t_rt*)data;
	rt->scene->angle = deg_to_rad(gtk_range_get_value(range));
}
