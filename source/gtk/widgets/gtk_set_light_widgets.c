/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_set_light_widgets.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:29:32 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:29:32 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

static void	gtk_set_light_type_list(GtkComboBoxText *type_combo)
{
	gtk_combo_box_text_append_text(type_combo, "AMBIENT");
	gtk_combo_box_text_append_text(type_combo, "POINT");
	gtk_combo_box_text_append_text(type_combo, "DIRECTION");
}

static void	gtk_set_light_name_type_widgets(t_gtk_light *gtk_light)
{
	gtk_light->grid = gtk_grid_new();
	gtk_light->name_label = gtk_label_new("Name:");
	gtk_widget_set_margin_start(gtk_light->name_label, 5);
	gtk_widget_set_margin_end(gtk_light->name_label, 5);
	gtk_widget_set_margin_top(gtk_light->name_label, 5);
	gtk_light->name_changer = gtk_entry_new();
	gtk_widget_set_margin_end(gtk_light->name_changer, 5);
	gtk_widget_set_margin_top(gtk_light->name_changer, 5);
	gtk_entry_set_max_length(GTK_ENTRY(gtk_light->name_changer), 20);
	gtk_light->type_label = gtk_label_new("Type:");
	gtk_widget_set_margin_start(gtk_light->type_label, 5);
	gtk_widget_set_margin_end(gtk_light->type_label, 5);
	gtk_widget_set_margin_top(gtk_light->type_label, 5);
	gtk_light->type_combo = gtk_combo_box_text_new();
	gtk_widget_set_margin_end(gtk_light->type_combo, 5);
	gtk_widget_set_margin_top(gtk_light->type_combo, 5);
	gtk_set_light_type_list(GTK_COMBO_BOX_TEXT(gtk_light->type_combo));
	gtk_combo_box_set_active(GTK_COMBO_BOX(gtk_light->type_combo), 0);
}

void		gtk_set_float_spinner(t_spinner *spinner, const char *name,
								cl_float value)
{
	spinner->label = gtk_label_new(name);
	gtk_widget_set_margin_start(spinner->label, 5);
	gtk_widget_set_margin_end(spinner->label, 5);
	gtk_set_spin_button_for_float(&spinner->spin, value);
}

static void	gtk_set_light_params_widgets(t_gtk_light *gtk_light, DTO_LIGHT *dto)
{
	gtk_light->intensity.label = gtk_label_new("Intensity:");
	gtk_widget_set_margin_start(gtk_light->intensity.label, 5);
	gtk_widget_set_margin_end(gtk_light->intensity.label, 5);
	gtk_set_spin_button_for_intensity(&gtk_light->intensity.spin,
									dto->intensity);
	gtk_light->params_frame = gtk_frame_new("Params");
	gtk_light->h_params = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_light->pos_grid = gtk_grid_new();
	gtk_light->pos_label = gtk_label_new("Position:");
	gtk_set_float_spinner(&gtk_light->pos_x, "X:", dto->position.x);
	gtk_set_float_spinner(&gtk_light->pos_y, "Y:", dto->position.y);
	gtk_set_float_spinner(&gtk_light->pos_z, "Z:", dto->position.z);
	gtk_light->dir_grid = gtk_grid_new();
	gtk_light->dir_label = gtk_label_new("Direction:");
	gtk_set_float_spinner(&gtk_light->dir_x, "X:", dto->direction.x);
	gtk_set_float_spinner(&gtk_light->dir_y, "Y:", dto->direction.y);
	gtk_set_float_spinner(&gtk_light->dir_z, "Z:", dto->direction.z);
}

void		gtk_set_light_widgets(t_gtk_light **gtk_light, SCENE *scene)
{
	struct s_light	*scene_light;

	scene_light = scene->lights;
	if ((*gtk_light = (t_gtk_light*)malloc(sizeof(t_gtk_light))) == NULL)
		ft_error("Can't allocate memory");
	(*gtk_light)->light = scene_light;
	(*gtk_light)->expander = gtk_expander_new_with_mnemonic("_Light");
	(*gtk_light)->frame = gtk_frame_new(scene_light->name);
	gtk_frame_set_label_align(GTK_FRAME((*gtk_light)->frame), 0.5, 0.0);
	gtk_set_light_name_type_widgets(*gtk_light);
	gtk_set_light_params_widgets(*gtk_light, scene_light->dto);
}
