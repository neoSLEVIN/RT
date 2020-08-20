#include "gtk_module.h"

void	gtk_set_buttons_positions(t_gtk_buttons *buttons)
{
	gtk_grid_attach(GTK_GRID(buttons->grid), buttons->add_shape,
		0, 0, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(buttons->grid), buttons->add_light,
		buttons->add_shape, GTK_POS_RIGHT, 1, 1);
}
