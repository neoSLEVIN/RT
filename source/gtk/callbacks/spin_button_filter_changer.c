#include "gtk_module.h"

void	spin_button_blur_filter_changer(GtkSpinButton *button, gpointer data)
{
	t_rt	*rt;

	(void)button;
	rt = (t_rt*)data;
	rt->scene->filter_params.x =
		gtk_spin_button_get_value(GTK_SPIN_BUTTON(button));
	update_filter_params(rt->ocl);
	rt->info->update = TRUE;
}

void	spin_button_sepia_filter_changer(GtkSpinButton *button, gpointer data)
{
	t_rt	*rt;

	(void)button;
	rt = (t_rt*)data;
	rt->scene->filter_params.y =
			gtk_spin_button_get_value(GTK_SPIN_BUTTON(button));
	update_filter_params(rt->ocl);
	rt->info->update = TRUE;
}

void	spin_button_noise_filter_changer(GtkSpinButton *button, gpointer data)
{
	t_rt	*rt;

	(void)button;
	rt = (t_rt*)data;
	rt->scene->filter_params.z =
			gtk_spin_button_get_value(GTK_SPIN_BUTTON(button));
	update_filter_params(rt->ocl);
	rt->info->update = TRUE;
}
