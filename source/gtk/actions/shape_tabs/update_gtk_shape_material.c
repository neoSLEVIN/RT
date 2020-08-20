#include "gtk_module.h"

void	update_gtk_shape_material(t_material_tab tab, MATERIAL shape_mat)
{
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(tab.transparency.spin),
							shape_mat.transparency);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(tab.reflective.spin),
							shape_mat.reflective);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(tab.specular.spin),
							shape_mat.specular);
}
