#include "gtk_module.h"

static void	do_invisible_params(t_main_tab *tab)
{
	gtk_widget_set_visible(tab->params_frame, FALSE);
	gtk_widget_set_visible(tab->h_radius, FALSE);
	gtk_widget_set_visible(tab->h_width, FALSE);
	gtk_widget_set_visible(tab->h_height, FALSE);
	gtk_widget_set_visible(tab->h_depth, FALSE);
	gtk_widget_set_visible(tab->h_angle, FALSE);
	//TODO new param for new shapes
}

static void	do_visible_params(t_main_tab *tab, SHAPE_TYPE type)
{
	if (type != PLANE && type != TRIANGLE)
		gtk_widget_set_visible(tab->params_frame, TRUE);
	if (type == PLANE || type == TRIANGLE)
		(void)type;
	else if (type == SPHERE || type == CYLINDER || type == CIRCLE)
		gtk_widget_set_visible(tab->h_radius, TRUE);
	else if (type == CONE)
		gtk_widget_set_visible(tab->h_angle, TRUE);
	else if (type == CAPPEDCYLINDER || type == CAPSULE)
	{
		gtk_widget_set_visible(tab->h_radius, TRUE);
		gtk_widget_set_visible(tab->h_height, TRUE);
	}
	else if (type == CAPPEDPLANE || type == BOX)
	{
		gtk_widget_set_visible(tab->h_width, TRUE);
		gtk_widget_set_visible(tab->h_height, TRUE);
		if (type == BOX)
			gtk_widget_set_visible(tab->h_depth, TRUE);
	}
	else
		ft_error("Unknown shape type (do_visible_params)");
}

static void	gtk_set_value_to_spin(t_spinner *spinner, cl_float value)
{
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(spinner->spin), value);
}

static void	update_gtk_shape_main_params(t_main_tab *tab, DTO_SHAPE *dto)
{
	if (dto->type == PLANE || dto->type == TRIANGLE)
		(void)dto;
	else if (dto->type == SPHERE || dto->type == CYLINDER ||
			dto->type == CIRCLE)
		gtk_set_value_to_spin(&tab->radius, dto->params.x);
	else if (dto->type == CONE)
		gtk_set_value_to_spin(&tab->angle, rad_to_deg(dto->params.x));
	else if (dto->type == CAPPEDCYLINDER || dto->type == CAPSULE)
	{
		gtk_set_value_to_spin(&tab->radius, dto->params.x);
		gtk_set_value_to_spin(&tab->height, dto->params.y);
	}
	else if (dto->type == CAPPEDPLANE || dto->type == BOX)
	{
		gtk_set_value_to_spin(&tab->width, dto->params.x);
		gtk_set_value_to_spin(&tab->height, dto->params.y);
		if (dto->type == BOX)
			gtk_set_value_to_spin(&tab->depth, dto->params.z);
	}
	else
		ft_error("Unknown shape type (update_gtk_shape_main_params)");
}

void		update_gtk_shape_main(t_main_tab tab, SHAPE *shape)
{
	gtk_entry_set_text(GTK_ENTRY(tab.name_changer), shape->name);
	gtk_editable_select_region(GTK_EDITABLE(tab.name_changer), 0, 0);
	gtk_combo_box_set_active(GTK_COMBO_BOX(tab.type_combo),
							shape->dto->type - 1);
	gtk_widget_grab_focus(tab.type_combo);
	do_invisible_params(&tab);
	do_visible_params(&tab, shape->dto->type);
	update_gtk_shape_main_params(&tab, shape->dto);
}
