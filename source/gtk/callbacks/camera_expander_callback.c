#include "gtk_module.h"

void	camera_expander_callback(GObject *object, GParamSpec *param_spec,
								gpointer data)
{
	t_rt			*rt;

	(void)param_spec;
	(void)object;
	rt = (t_rt*)data;
	g_idle_add(update_camera_widget, rt);
}
