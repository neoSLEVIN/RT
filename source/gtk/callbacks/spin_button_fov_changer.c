#include "gtk_module.h"

void	spin_button_fov_changer(GtkSpinButton *button, gpointer data)
{
	t_rt	*rt;

	(void)button;
	rt = (t_rt*)data;
	rt->scene->cam.fov = gtk_spin_button_get_value(GTK_SPIN_BUTTON(button));
	init_dto_cam(rt->scene->cam.dto, rt->scene->cam.fov);
	rt->info->update_cam = TRUE;
	rt->info->update = TRUE;
}
