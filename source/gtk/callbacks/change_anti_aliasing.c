#include "gtk_module.h"

void	change_anti_aliasing(GtkToggleButton *toggle_button, gpointer data)
{
	t_rt	*rt;

	(void)toggle_button;
	rt = (t_rt*)data;
	rt->scene->anti_aliasing = rt->scene->anti_aliasing ? 0 : 1;
	update_anti_aliasing_arg(rt->ocl);
	rt->info->update = TRUE;
}
