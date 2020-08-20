#include "gtk_module.h"

static gboolean	spin_button_shape_position_changer_safe(gpointer data)
{
	int				i;
	t_rt			*rt;
	FLT3			*position;
	FLT3			temp_position;
	t_transform_tab	*transform;

	rt = (t_rt*)data;
	ASSERT_SHAPE(rt->gtk->ui.shape->shape);
	position = &rt->gtk->ui.shape->shape->dto->transform.position;
	temp_position = *position;
	transform = &rt->gtk->ui.shape->transform;
	position->x = gtk_spin_button_get_value(GTK_SPIN_BUTTON(transform->x.spin));
	position->y = gtk_spin_button_get_value(GTK_SPIN_BUTTON(transform->y.spin));
	position->z = gtk_spin_button_get_value(GTK_SPIN_BUTTON(transform->z.spin));
	temp_position = v3_sub(*position, temp_position);
	i = -1;
	while (++i < SECTION_CNT)
	{
		position = &rt->gtk->ui.shape->shape->dto->sections[i].position;
		*position = v3_add(*position, temp_position);
	}
	update_flags(&rt->info->update_shapes, &rt->info->update);
	update_shapes_arg(rt->ocl, &rt->info->update_s_cnt,
					&rt->info->update_shapes);
	return (FALSE);
}

void			spin_button_shape_position_changer(GtkSpinButton *button,
												gpointer data)
{
	(void)button;
	g_idle_add(spin_button_shape_position_changer_safe, data);
}
