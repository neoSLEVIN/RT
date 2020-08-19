#include "gtk_module.h"

void	spin_button_shape_material_changer(GtkSpinButton *button, gpointer data)
{
	t_rt			*rt;
	MATERIAL		*material;
	t_material_tab	*material_tab;

	(void)button;
	rt = (t_rt*)data;
	material = &rt->gtk->ui.shape->shape->dto->material;
	material_tab = &rt->gtk->ui.shape->material;
	material->transparency = gtk_spin_button_get_value(
			GTK_SPIN_BUTTON(material_tab->transparency.spin));
	material->reflective = gtk_spin_button_get_value(
			GTK_SPIN_BUTTON(material_tab->reflective.spin));
	material->specular = gtk_spin_button_get_value(
			GTK_SPIN_BUTTON(material_tab->specular.spin));
	rt->info->update_shapes = TRUE;
	update_shapes_arg(rt->ocl, &rt->info->update_s_cnt,
					&rt->info->update_shapes);
	draw_image(rt);
}
