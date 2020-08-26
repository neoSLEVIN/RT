#include "gtk_module.h"

void	gtk_set_scale(t_scale *scale, INT2 range, int value, const char *label)
{
	GtkAdjustment	*adj;

	scale->label = gtk_label_new(label);
	gtk_widget_set_hexpand(scale->label, FALSE);
	adj = gtk_adjustment_new(value, range.x, range.y, 1, 1, 0);
	scale->scale = gtk_scale_new(GTK_ORIENTATION_HORIZONTAL, adj);
	gtk_scale_set_digits(GTK_SCALE(scale->scale), 0);
	gtk_widget_set_hexpand(scale->scale, TRUE);
}
