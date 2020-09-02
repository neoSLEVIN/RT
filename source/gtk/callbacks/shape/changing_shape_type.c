#include "gtk_module.h"

void	primitive_calculation_for_triangle_dots(DTO_SHAPE *dto)
{
	FLT3	two_dot_sum;
	FLT3	*pos;
	FLT3	*params;

	pos = &dto->transform.position;
	params = dto->params;
	if (v3_length(v3_sub(v3_scale(*pos, 3),
		v3_add(v3_add(params[0], params[1]), params[2]))) <= 0.001f)
		return ;
	if (v3_length(v3_sub(*pos, params[0])) <= 0.001f)
		params[0] = v3_add(v3_scale(*pos, 2), (FLT3){1.0f, 0.0f, 0.0f});
	two_dot_sum = v3_sub(v3_scale(*pos, 3.0f), params[0]);
	params[1] = (FLT3){two_dot_sum.x, two_dot_sum.y, 0};
	params[2] = (FLT3){0, 0, two_dot_sum.z};
}

static gboolean	changing_shape_type_safe(gpointer data)
{
	t_rt	*rt;

	rt = (t_rt*)data;
	ASSERT_SHAPE(rt->gtk->ui.shape->shape);
	gtk_tree_store_set(rt->gtk->ui.shapes.store,
		(GtkTreeIter*)rt->gtk->ui.shape->shape->tree_iter,
		S_TYPE_COL, get_shape_type_name(rt->gtk->ui.shape->shape->dto->type),
		-1);
	if (rt->gtk->ui.shape->shape->dto->type == TRIANGLE)
	{
		primitive_calculation_for_triangle_dots(rt->gtk->ui.shape->shape->dto);
	}
	else
		do_change_shape_param(rt->gtk->ui.shape->shape->dto->params,
							rt->gtk->ui.shape->shape->dto->type, 0);
	rt->info->update_shapes = TRUE;
	update_shapes_arg(rt->ocl, &rt->info->update_s_cnt,
					&rt->info->update_shapes);
	rt->info->update_s_main = TRUE;
	rt->info->update = TRUE;
	return (FALSE);
}


void		changing_shape_type(GtkComboBox *type_combo, gpointer data)
{
	t_rt	*rt;

	rt = (t_rt*)data;
	ASSERT_SHAPE_VOID(rt->gtk->ui.shape->shape);
	rt->gtk->ui.shape->shape->dto->type =
			gtk_combo_box_get_active(type_combo) + 1;
	g_idle_add(changing_shape_type_safe, data);
}
