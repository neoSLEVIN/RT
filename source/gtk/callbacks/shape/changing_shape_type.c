#include "gtk_module.h"

void	changing_shape_type(GtkComboBox *type_combo, gpointer data)
{
	t_rt	*rt;

	rt = (t_rt*)data;
	ASSERT_SHAPE_VOID(rt->gtk->ui.shape->shape);
	rt->gtk->ui.shape->shape->dto->type =
			gtk_combo_box_get_active(type_combo) + 1;
	gtk_tree_store_set(rt->gtk->ui.shapes.store,
		(GtkTreeIter*)rt->gtk->ui.shape->shape->tree_iter,
		S_TYPE_COL, get_shape_type_name(rt->gtk->ui.shape->shape->dto->type),
		-1);
	do_change_shape_param(&rt->gtk->ui.shape->shape->dto->params,
						rt->gtk->ui.shape->shape->dto->type, 0);
	rt->info->update_shapes = TRUE;
	update_shapes_arg(rt->ocl, &rt->info->update_s_cnt,
					&rt->info->update_shapes);
	rt->info->update_s_main = TRUE;
	rt->info->update = TRUE;
}
