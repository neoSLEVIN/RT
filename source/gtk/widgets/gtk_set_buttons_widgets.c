#include "gtk_module.h"

void	gtk_set_buttons_widgets(t_gtk_buttons *buttons)
{
	buttons->grid = gtk_grid_new();
	buttons->add_shape = gtk_button_new_with_mnemonic("_New shape");
	gtk_widget_set_halign(buttons->add_shape, GTK_ALIGN_START);
	gtk_button_set_image_position(GTK_BUTTON(buttons->add_shape), GTK_POS_TOP);
	gtk_button_set_always_show_image(GTK_BUTTON(buttons->add_shape), TRUE);
	gtk_button_set_image(GTK_BUTTON(buttons->add_shape),
		gtk_image_new_from_file("extras/icons/new_shape.png"));
}
