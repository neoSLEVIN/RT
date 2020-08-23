#include "gtk_module.h"

void	color_activated_changer(GtkColorChooser *chooser,
								GParamSpec *param_spec, gpointer data)
{
	t_rt	*rt;
	GdkRGBA	color;

	(void)param_spec;
	if (!gtk_widget_get_visible(GTK_WIDGET(chooser)))
		return ;
	rt = (t_rt*)data;
	ASSERT_SHAPE_VOID(rt->gtk->ui.shape->shape);
	gtk_color_chooser_get_rgba(chooser, &color);
	rt->gtk->ui.shape->shape->dto->material.color =
			(FLT3){(float)color.red, (float)color.green, (float)color.blue};
	rt->info->update_shapes = TRUE;
	update_shapes_arg(rt->ocl, &rt->info->update_s_cnt,
					&rt->info->update_shapes);
	rt->info->update = TRUE;
}
