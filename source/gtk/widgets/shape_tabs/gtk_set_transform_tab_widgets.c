#include "gtk_module.h"

void	gtk_set_transform_tab_widgets(t_transform_tab *tab,
									TRANSFORM *shape_transform)
{
	tab->label = gtk_label_new("Transform");
	tab->grid = gtk_grid_new();
	tab->label_pos = gtk_label_new("Position:");
	gtk_widget_set_margin_top(tab->label_pos, 5);
	gtk_widget_set_margin_bottom(tab->label_pos, 5);
	tab->x.label = gtk_label_new("X:");
	gtk_widget_set_margin_start(tab->x.label, 5);
	gtk_widget_set_margin_end(tab->x.label, 5);
	gtk_set_spin_button_for_float(&tab->x.spin, shape_transform->position.x);
	tab->y.label = gtk_label_new("Y:");
	gtk_set_spin_button_for_float(&tab->y.spin, shape_transform->position.y);
	tab->z.label = gtk_label_new("Z:");
	gtk_set_spin_button_for_float(&tab->z.spin, shape_transform->position.z);
}
