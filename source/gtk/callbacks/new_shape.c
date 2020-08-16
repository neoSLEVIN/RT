#include "gtk_module.h"

static SHAPE	*gtk_new_shape_init(t_rt *rt)
{
	SHAPE	*shape;
	SHAPE	*temp;

	if (!(shape = (SHAPE*)malloc(sizeof(SHAPE))))
		ft_error("Can't allocate memory");
	get_default_shape(shape, &rt->info->default_shape_dto);
	init_default_shape_dto(&rt->ocl->dto.cam, shape->dto);
	if (!(shape->name = ft_strdup("Shape")))
		ft_error("Can't allocate memory");
	if (rt->scene->shapes == NULL)
	{
		rt->scene->shapes = shape;
		return (shape);
	}
	temp = rt->scene->shapes;
	while (temp->next)
		temp = temp->next;
	temp->next = shape;
	shape->prev = temp;
	return (shape);
}

void		gtk_new_shape_update_everything(t_rt *rt,
										t_gtk_shapes *gtk_shapes, SHAPE *shape)
{
	gtk_tree_store_append(gtk_shapes->store, &gtk_shapes->iter, NULL);
	if (!(shape->tree_iter = (void*)gtk_tree_iter_copy(&gtk_shapes->iter)))
		ft_error("Can't allocate memory");
	gtk_tree_store_set(gtk_shapes->store, &gtk_shapes->iter,
						S_NAME_COL, shape->name,
						S_TYPE_COL, get_shape_type_name(shape->dto->type),
						S_MARKER_COL, shape->dto->marker,
						S_POINTER_COL, shape,
						-1);
	realloc_shapes_dto(&rt->ocl->dto.shapes, rt->scene->shapes,
					++rt->scene->s_cnt);
	update_shape_marker(rt, shape);
	update_shapes_flags(&rt->info->update_shapes, &rt->info->update_s_cnt);
	update_shapes_arg(rt->ocl, &rt->info->update_s_cnt,
					&rt->info->update_shapes);
	rt->info->update = TRUE;
	rt->gtk->ui.shape->shape = shape;
	shape_to_true(rt->info);
	g_idle_add(update_shape_widget, rt);
}

void			new_shape(GtkButton *button, gpointer data)
{
	t_rt	*rt;
	SHAPE	*shape;

	(void)button;
	rt = (t_rt*)data;
	shape = gtk_new_shape_init(rt);
	gtk_new_shape_update_everything(rt, &rt->gtk->ui.shapes, shape);
}
