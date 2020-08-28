#include "gtk_module.h"

void	gtk_set_color_tab_widgets(t_color_tab *color_tab, FLT3 *color)
{
	color_tab->label = gtk_label_new("Texture/Color");
	color_tab->scrolled_window = gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_min_content_width(GTK_SCROLLED_WINDOW(
		color_tab->scrolled_window), 370);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(
		color_tab->scrolled_window),
		GTK_POLICY_AUTOMATIC, GTK_POLICY_NEVER);
	color_tab->v_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	color_tab->color = gtk_color_chooser_widget_new();
	gtk_color_chooser_set_use_alpha(GTK_COLOR_CHOOSER(color_tab->color), FALSE);
	g_object_set(color_tab->color, "show-editor", TRUE, NULL);
	gtk_color_chooser_set_rgba(GTK_COLOR_CHOOSER(color_tab->color),
		&(GdkRGBA){color->x, color->y, color->z, 1});
	gtk_widget_set_margin_top(color_tab->color, 10);
	gtk_widget_set_margin_bottom(color_tab->color, 15);
}
