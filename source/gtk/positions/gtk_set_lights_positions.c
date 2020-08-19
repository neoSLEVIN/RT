#include "gtk_module.h"

void	gtk_set_lights_positions(t_gtk_lights *lights)
{
	gtk_container_add(GTK_CONTAINER(lights->expander), lights->scrolled_window);
	gtk_container_add(GTK_CONTAINER(lights->scrolled_window), lights->tree);
}
