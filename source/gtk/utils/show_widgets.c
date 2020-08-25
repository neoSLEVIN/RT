#include "gtk_module.h"

void	show_widgets(t_rt *rt)
{
	FILTER	filter;

	gtk_widget_show_all(rt->gtk->window);
	filter = rt->scene->filter;
	if (filter == BLUR || filter == SEPIA || filter == NOISE)
	{
		gtk_widget_set_visible(rt->gtk->ui.settings.v_filter_params, TRUE);
		gtk_widget_set_visible(rt->gtk->ui.settings.h_blur, filter == BLUR);
		gtk_widget_set_visible(rt->gtk->ui.settings.h_sepia, filter == SEPIA);
		gtk_widget_set_visible(rt->gtk->ui.settings.h_noise, filter == NOISE);
	}
	else
		gtk_widget_set_visible(rt->gtk->ui.settings.v_filter_params, FALSE);
}
