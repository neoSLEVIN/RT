#include "gtk_module.h"

void	gtk_set_shape_color_positions(t_color_tab *color)
{
	gtk_container_add(GTK_CONTAINER(color->scrolled_window), color->color);
}
