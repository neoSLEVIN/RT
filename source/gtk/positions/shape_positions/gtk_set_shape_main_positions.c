#include "gtk_module.h"

static void	gtk_set_shape_main_base_positions(t_main_tab *main_tab)
{
	gtk_grid_attach(GTK_GRID(main_tab->grid), main_tab->name_label,
		0, 0, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(main_tab->grid), main_tab->name_changer,
		main_tab->name_label, GTK_POS_RIGHT, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(main_tab->grid), main_tab->type_label,
		main_tab->name_label, GTK_POS_BOTTOM, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(main_tab->grid), main_tab->type_combo,
		main_tab->type_label, GTK_POS_RIGHT, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(main_tab->grid), main_tab->params_frame,
		main_tab->name_changer, GTK_POS_RIGHT, 1, 10);
}

static void	gtk_set_shape_main_params_boxes_positions(t_main_tab *main_tab)
{
	gtk_container_add(GTK_CONTAINER(main_tab->params_frame),
		main_tab->v_params);
	gtk_box_pack_start(GTK_BOX(main_tab->v_params), main_tab->h_radius,
		FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(main_tab->v_params), main_tab->h_width,
		FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(main_tab->v_params), main_tab->h_height,
		FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(main_tab->v_params), main_tab->h_angle,
		FALSE, FALSE, 0);
	//TODO add boxes
}

static void	gtk_set_shape_main_params_positions(t_main_tab *main_tab)
{
	gtk_box_pack_start(GTK_BOX(main_tab->h_radius), main_tab->radius.label,
		FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(main_tab->h_radius), main_tab->radius.spin,
		FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(main_tab->h_width), main_tab->width.label,
		FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(main_tab->h_width), main_tab->width.spin,
		FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(main_tab->h_height), main_tab->height.label,
		FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(main_tab->h_height), main_tab->height.spin,
		FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(main_tab->h_angle), main_tab->angle.label,
		FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(main_tab->h_angle), main_tab->angle.spin,
		FALSE, FALSE, 0);
	//TODO add params
}

void		gtk_set_shape_main_positions(t_main_tab *main_tab)
{
	gtk_set_shape_main_base_positions(main_tab);
	gtk_set_shape_main_params_boxes_positions(main_tab);
	gtk_set_shape_main_params_positions(main_tab);
}
