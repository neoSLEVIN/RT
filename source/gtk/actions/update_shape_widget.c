/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_shape_widget.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 06:58:24 by cschoen           #+#    #+#             */
/*   Updated: 2020/06/01 21:36:08 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

static void	update_shape_tab_widget(t_rt *rt, t_gtk_shape *shape,
													gint current_page)
{
	if (current_page == MAIN_TAB && rt->info->update_s_main)
		update_gtk_shape_main(shape->main, shape->shape);
	else if (current_page == TRANSFORM_TAB && rt->info->update_s_pos)
		update_gtk_shape_position(shape->transform, shape->shape->dto);
	else if (current_page == MATERIAL_TAB && rt->info->update_s_mat)
		update_gtk_shape_material(shape->material, shape->shape->dto->material);
	else if (current_page == TEXTURE_COLOR_TAB &&
			(rt->info->update_s_col || rt->info->update_s_tex))
	{
		update_gtk_shape_color(&shape->color,
								shape->shape->dto->material.color);
		update_gtk_shape_texture(shape->texture,
								shape->shape->dto->texture.id,
								shape->shape->dto->normal_map.id);
	}
	else if (current_page == SECTION_TAB && rt->info->update_s_sec)
		update_gtk_shape_section(shape->section, shape->shape->dto->sections,
								shape->shape->dto->is_complex_section);
}

gboolean	update_shape_widget(gpointer data)
{
	t_rt		*rt;
	t_gtk_shape	*shape;
	gint		current_page;

	rt = (t_rt*)data;
	shape = rt->gtk->ui.shape;
	ASSERT_SHAPE(rt->gtk->ui.shape->shape);
	if (gtk_expander_get_expanded(GTK_EXPANDER(shape->expander)))
	{
		current_page =
			gtk_notebook_get_current_page(GTK_NOTEBOOK(shape->notebook));
		if (rt->info->update_s_name)
			gtk_frame_set_label(GTK_FRAME(shape->frame), shape->shape->name);
		update_shape_tab_widget(rt, shape, current_page);
	}
	shape_to_false(rt->info);
	return (FALSE);
}
