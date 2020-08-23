#include "gtk_module.h"

void	update_gtk_shape_color(t_color_tab tab, FLT3 color)
{
	if (!gtk_widget_get_visible(tab.color))
		gtk_widget_set_visible(tab.color, TRUE);
	gtk_color_chooser_set_rgba(GTK_COLOR_CHOOSER(tab.color),
							&(GdkRGBA){color.x, color.y, color.z, 1});
}
