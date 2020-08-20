#include "gtk_module.h"

void	update_gtk_shape_texture(t_texture_tab tab,
								int texture_id, int normal_map_id)
{
	gtk_combo_box_set_active(GTK_COMBO_BOX(tab.texture_combo),
							texture_id + 5);
	gtk_combo_box_set_active(GTK_COMBO_BOX(tab.normals_combo),
							normal_map_id + 1);
}
