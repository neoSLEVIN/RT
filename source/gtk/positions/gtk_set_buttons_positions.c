#include "gtk_module.h"

void	gtk_set_buttons_positions(t_gtk_buttons *buttons)
{
	gtk_grid_attach(GTK_GRID(buttons->grid), buttons->add_shape,
		0, 0, 1, 1);
}
