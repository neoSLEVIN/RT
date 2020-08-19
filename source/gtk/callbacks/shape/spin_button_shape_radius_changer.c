#include "gtk_module.h"

static gboolean	spin_button_shape_radius_changer_safe(gpointer data)
{
	t_rt	*rt;
	FLT3	*params;

	rt = (t_rt*)data;
	params = &rt->gtk->ui.shape->shape->dto->params;
	params->x = gtk_spin_button_get_value(GTK_SPIN_BUTTON(
										rt->gtk->ui.shape->main.radius.spin));
	rt->info->update_shapes = TRUE;
	update_shapes_arg(rt->ocl, &rt->info->update_s_cnt,
					&rt->info->update_shapes);
	rt->info->update = TRUE;
	return (FALSE);
}

void			spin_button_shape_radius_changer(GtkSpinButton *button,
												gpointer data)
{
	(void)button;
	g_idle_add(spin_button_shape_radius_changer_safe, data);
}
