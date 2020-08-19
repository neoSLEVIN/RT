#include "gtk_module.h"

static SHAPE	*new_shape_init(t_rt *rt)
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

void			new_shape(GtkButton *button, gpointer data)
{
	t_rt	*rt;
	SHAPE	*shape;

	(void)button;
	rt = (t_rt*)data;
	shape = new_shape_init(rt);
	new_shape_update_everything(rt, &rt->gtk->ui.shapes, shape);
}
