#include "gtk_module.h"

void	gtk_set_material_tab_widgets(t_material_tab *material_tab,
												MATERIAL *shape_material)
{
	material_tab->label = gtk_label_new("Material");
	material_tab->grid = gtk_grid_new();
	material_tab->transparency.label = gtk_label_new("Transparency:");
	material_tab->reflective.label = gtk_label_new("Reflective:");
	material_tab->specular.label = gtk_label_new("Specular:");
	gtk_widget_set_margin_start(material_tab->transparency.label, 5);
	gtk_widget_set_margin_end(material_tab->transparency.label, 5);
	gtk_set_spin_button_for_one(&material_tab->transparency.spin,
								shape_material->transparency);
	gtk_set_spin_button_for_one(&material_tab->reflective.spin,
								shape_material->reflective);
	gtk_set_spin_button_for_one(&material_tab->specular.spin,
								shape_material->specular);
	gtk_widget_set_margin_top(material_tab->transparency.spin, 5);
}
