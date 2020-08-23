#include "gtk_module.h"

void	update_gtk_shape_position(t_transform_tab tab, FLT3 shape_pos)
{
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(tab.x.spin), shape_pos.x);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(tab.y.spin), shape_pos.y);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(tab.z.spin), shape_pos.z);
}
