#include "gtk_module.h"

void	changing_light_type(GtkComboBox *type_combo, gpointer data)
{
	t_rt	*rt;

	rt = (t_rt*)data;
	ASSERT_LIGHT_VOID(rt->gtk->ui.light->light);
	rt->gtk->ui.light->light->dto->type = gtk_combo_box_get_active(type_combo);
	gtk_tree_store_set(rt->gtk->ui.lights.store,
		(GtkTreeIter*)rt->gtk->ui.light->light->tree_iter,
		LIGHT_TYPE_COL,
		get_light_type_name(rt->gtk->ui.light->light->dto->type),
		-1);
	rt->info->update_lights = TRUE;
	update_lights_arg(rt->ocl, &rt->info->update_l_cnt,
					&rt->info->update_lights);
	rt->info->update_l_params = TRUE;
	g_idle_add(update_light_widget, rt);
	rt->info->update = TRUE;
}
