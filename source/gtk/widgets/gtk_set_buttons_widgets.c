#include "gtk_module.h"

static void	gtk_set_button_image(GtkWidget **button, const char *mnemonic_label,
								const char *filename)
{
	*button = gtk_button_new_with_mnemonic(mnemonic_label);
	gtk_widget_set_halign(*button, GTK_ALIGN_START);
	gtk_button_set_image_position(GTK_BUTTON(*button), GTK_POS_TOP);
	gtk_button_set_always_show_image(GTK_BUTTON(*button), TRUE);
	gtk_button_set_image(GTK_BUTTON(*button),
						gtk_image_new_from_file(filename));
}

void		gtk_set_buttons_widgets(t_gtk_buttons *buttons)
{
	buttons->grid = gtk_grid_new();
	gtk_set_button_image(&buttons->add_shape, "_New shape",
						"icons/new_shape.png");
	gtk_set_button_image(&buttons->add_light, "Ne_w light",
						"icons/new_light.png");
}
