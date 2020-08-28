#include "gtk_module.h"

void	gtk_set_material_tab_widgets(t_material_tab *material_tab,
												MATERIAL *shape_material)
{
	material_tab->label = gtk_label_new("Material");
	material_tab->grid = gtk_grid_new();
	material_tab->transparency =
		gtk_get_float_scale("Transparency:", (FLT2){0, 1},
			shape_material->transparency, 0.005);
	material_tab->reflective =
			gtk_get_float_scale("Reflective:", (FLT2){0, 1},
				shape_material->reflective, 0.005);
	material_tab->specular =
			gtk_get_float_scale("Specular:", (FLT2){0, 1},
				shape_material->specular, 0.005);
}
