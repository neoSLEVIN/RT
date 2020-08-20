#include "gtk_module.h"

void	gtk_set_shape_transform_positions(t_transform_tab *tab)
{
	gtk_grid_attach(GTK_GRID(tab->grid), tab->label_pos,
		0, 0, 2, 1);
	gtk_grid_attach_next_to(GTK_GRID(tab->grid), tab->x.label,
		tab->label_pos, GTK_POS_BOTTOM, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(tab->grid), tab->y.label,
		tab->x.label, GTK_POS_BOTTOM, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(tab->grid), tab->z.label,
		tab->y.label, GTK_POS_BOTTOM, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(tab->grid), tab->x.spin,
		tab->x.label, GTK_POS_RIGHT, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(tab->grid), tab->y.spin,
		tab->y.label, GTK_POS_RIGHT, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(tab->grid), tab->z.spin,
		tab->z.label, GTK_POS_RIGHT, 1, 1);
}
