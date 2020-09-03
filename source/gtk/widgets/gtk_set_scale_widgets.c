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

t_scale	gtk_get_float_scale(const char *label, FLT2 range, cl_float value,
							cl_float step)
{
	t_scale			scale;
	GtkAdjustment	*adj;

	scale.label = gtk_label_new(label);
	gtk_widget_set_hexpand(scale.label, FALSE);
	gtk_widget_set_margin_start(scale.label, 5);
	gtk_widget_set_margin_top(scale.label, 5);
	adj = gtk_adjustment_new(value, range.x, range.y, step, 1, 0);
	scale.scale = gtk_scale_new(GTK_ORIENTATION_HORIZONTAL, adj);
	gtk_scale_set_digits(GTK_SCALE(scale.scale), 3);
	gtk_widget_set_hexpand(scale.scale, TRUE);
	gtk_widget_set_margin_top(scale.scale, 5);
	return (scale);
}
