#include "gtk_module.h"

void	changing_texture_type(GtkComboBox *texture_combo, gpointer data)
{
	t_rt	*rt;

	rt = (t_rt*)data;
	rt->gtk->ui.shape->shape->dto->texture.id =
			gtk_combo_box_get_active(texture_combo) - 5;
	rt->info->update_shapes = TRUE;
	update_shapes_arg(rt->ocl, &rt->info->update_s_cnt,
					&rt->info->update_shapes);
	rt->info->update = TRUE;
}

void	changing_normals_type(GtkComboBox *normals_combo, gpointer data)
{
	t_rt	*rt;

	rt = (t_rt*)data;
	rt->gtk->ui.shape->shape->dto->normal_map.id =
			gtk_combo_box_get_active(normals_combo) - 1;
	rt->info->update_shapes = TRUE;
	update_shapes_arg(rt->ocl, &rt->info->update_s_cnt,
					&rt->info->update_shapes);
	rt->info->update = TRUE;
}
