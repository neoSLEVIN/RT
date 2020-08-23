#include "gtk_module.h"

void	switch_page_shape_notebook(GtkNotebook *notebook, GtkWidget *page,
												guint page_num, gpointer data)
{
	t_rt	*rt;

	(void)notebook;
	(void)page;
	rt = (t_rt*)data;
	if (page_num == MAIN_TAB)
		rt->info->update_s_main = TRUE;
	else if (page_num == TRANSFORM_TAB)
		rt->info->update_s_pos = TRUE;
	else if (page_num == MATERIAL_TAB)
		rt->info->update_s_mat = TRUE;
	else if (page_num == COLOR_TAB)
		rt->info->update_s_col = TRUE;
	else if (page_num == TEXTURE_TAB)
		rt->info->update_s_tex = TRUE;
	else if (page_num == SECTION_TAB)
		rt->info->update_s_sec = TRUE;
	else
		ft_error("Update flag for unknown page in switch_page_shape_notebook, "
				"update_shape_widget");
	g_idle_add(update_shape_widget, rt);
}
