#include "gtk_module.h"

void	shape_expander_callback(GObject *object, GParamSpec *param_spec,
								gpointer data)
{
	t_rt		*rt;
	GtkExpander	*expander;

	(void)param_spec;
	rt = (t_rt*)data;
	expander = GTK_EXPANDER(object);
	if (gtk_expander_get_expanded(expander))
	{
		if (rt->gtk->ui.shape->shape == NULL)
			return (gtk_expander_set_expanded(expander, FALSE));
		shape_to_true(rt->info);
		g_idle_add(update_shape_widget, rt);
	}
}
