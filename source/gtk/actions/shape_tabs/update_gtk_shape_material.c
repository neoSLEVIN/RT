#include "gtk_module.h"

void	update_gtk_shape_material(t_material_tab tab, MATERIAL shape_mat)
{
	gtk_range_set_value(GTK_RANGE(tab.transparency.scale),
						shape_mat.transparency);
	gtk_range_set_value(GTK_RANGE(tab.reflective.scale),
						shape_mat.reflective);
	gtk_range_set_value(GTK_RANGE(tab.specular.scale),
						shape_mat.specular);
}
