#include "gtk_module.h"

void	gtk_set_shape_texture_positions(t_texture_tab *texture)
{
	gtk_grid_attach(GTK_GRID(texture->grid), texture->texture_label,
		0, 0, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(texture->grid),
		texture->texture_combo, texture->texture_label,
		GTK_POS_RIGHT, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(texture->grid),
		texture->normals_label, texture->texture_label,
		GTK_POS_BOTTOM, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(texture->grid),
		texture->normals_combo, texture->normals_label,
		GTK_POS_RIGHT, 1, 1);
}
