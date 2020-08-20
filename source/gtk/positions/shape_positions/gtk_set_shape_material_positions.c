#include "gtk_module.h"

void	gtk_set_shape_material_positions(t_material_tab *material)
{
	gtk_grid_attach(GTK_GRID(material->grid), material->transparency.label,
		0, 0, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(material->grid),
		material->reflective.label, material->transparency.label,
		GTK_POS_BOTTOM, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(material->grid),
		material->specular.label, material->reflective.label,
		GTK_POS_BOTTOM, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(material->grid),
		material->transparency.spin, material->transparency.label,
		GTK_POS_RIGHT, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(material->grid),
		material->reflective.spin, material->reflective.label,
		GTK_POS_RIGHT, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(material->grid),
		material->specular.spin, material->specular.label,
		GTK_POS_RIGHT, 1, 1);
}
