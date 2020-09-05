/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_light_widget.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:22:46 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:22:46 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

static void	update_gtk_light_params(t_gtk_light *light, DTO_LIGHT *dto)
{
	if (dto->type == AMBIENT)
		(void)dto;
	else if (dto->type == POINT)
	{
		gtk_spin_button_set_value(GTK_SPIN_BUTTON(light->pos_x.spin),
								dto->position.x);
		gtk_spin_button_set_value(GTK_SPIN_BUTTON(light->pos_y.spin),
								dto->position.y);
		gtk_spin_button_set_value(GTK_SPIN_BUTTON(light->pos_z.spin),
								dto->position.z);
	}
	else if (dto->type == DIRECTION)
	{
		gtk_spin_button_set_value(GTK_SPIN_BUTTON(light->dir_x.spin),
								dto->direction.x);
		gtk_spin_button_set_value(GTK_SPIN_BUTTON(light->dir_y.spin),
								dto->direction.y);
		gtk_spin_button_set_value(GTK_SPIN_BUTTON(light->dir_z.spin),
								dto->direction.z);
	}
	else
		ft_error("Unknown shape type (update_gtk_light_params)");
}

static void	change_vision_of_light_params(t_gtk_light *light, LIGHT_TYPE type)
{
	gtk_widget_set_visible(light->params_frame, (type != AMBIENT));
	gtk_widget_set_visible(light->pos_grid, (type == POINT));
	gtk_widget_set_visible(light->dir_grid, (type == DIRECTION));
	if (type == AMBIENT || type == POINT || type == DIRECTION)
		(void)light;
	else
		ft_error("Unknown light type (change_vision_of_light_params)");
}

gboolean	update_light_widget(gpointer data)
{
	t_rt		*rt;
	t_gtk_light	*light;

	rt = (t_rt*)data;
	ASSERT_LIGHT(rt->gtk->ui.light->light);
	light = rt->gtk->ui.light;
	if (gtk_expander_get_expanded(GTK_EXPANDER(light->expander)))
	{
		if (rt->info->update_l_name)
			gtk_frame_set_label(GTK_FRAME(light->frame), light->light->name);
		gtk_entry_set_text(GTK_ENTRY(light->name_changer), light->light->name);
		gtk_combo_box_set_active(GTK_COMBO_BOX(light->type_combo),
			light->light->dto->type);
		gtk_spin_button_set_value(GTK_SPIN_BUTTON(light->intensity.spin),
			light->light->dto->intensity);
		if (rt->info->update_l_params)
		{
			change_vision_of_light_params(light, light->light->dto->type);
			update_gtk_light_params(light, light->light->dto);
		}
	}
	rt->info->update_l_name = FALSE;
	rt->info->update_l_params = FALSE;
	return (FALSE);
}
