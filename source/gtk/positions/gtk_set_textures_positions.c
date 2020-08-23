#include "gtk_module.h"

void	gtk_set_textures_positions(t_gtk_textures *textures)
{
	gtk_container_add(GTK_CONTAINER(textures->expander),
					textures->scrolled_window);
	gtk_container_add(GTK_CONTAINER(textures->scrolled_window), textures->tree);
}
