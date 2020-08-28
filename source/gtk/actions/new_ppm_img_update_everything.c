#include "gtk_module.h"

void		new_ppm_img_update_everything(t_rt *rt, t_gtk_textures *gtk_ppm,
										PPM_IMG *new_texture,
										_Bool is_normal_map)
{
	gtk_tree_store_append(gtk_ppm->store, &gtk_ppm->iter, NULL);
	gtk_tree_store_set(gtk_ppm->store, &gtk_ppm->iter,
					0, new_texture->name,
					1, new_texture->path,
					-1);
	if (is_normal_map)
	{
		realloc_ppm_img_dto(&rt->ocl->dto.normal_maps, rt->scene->normal_maps,
							++rt->scene->n_cnt);
		update_textures_arg(rt->ocl, rt->scene->n_cnt);
		gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(
			rt->gtk->ui.shape->texture.normals_combo), new_texture->name);
	}
	else
	{
		realloc_ppm_img_dto(&rt->ocl->dto.textures, rt->scene->textures,
							++rt->scene->t_cnt);
		update_textures_arg(rt->ocl, rt->scene->t_cnt);
		gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(
			rt->gtk->ui.shape->texture.texture_combo), new_texture->name);
	}
}
