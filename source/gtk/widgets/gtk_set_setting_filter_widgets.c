#include "gtk_module.h"

static void	gtk_set_filters_list(GtkComboBoxText *filter_combo)
{
	gtk_combo_box_text_append_text(filter_combo, "NO FILTER");
	gtk_combo_box_text_append_text(filter_combo, "SEPIA");
	gtk_combo_box_text_append_text(filter_combo, "NEGATIVE");
	gtk_combo_box_text_append_text(filter_combo, "NOISE");
	gtk_combo_box_text_append_text(filter_combo, "SHADES OF GRAY");
	gtk_combo_box_text_append_text(filter_combo, "BLUR");
	gtk_combo_box_text_append_text(filter_combo, "EMBOSS");
	gtk_combo_box_text_append_text(filter_combo, "SHARPEN");
}

static void	gtk_set_spin_button_for_filter(GtkWidget **spin, cl_float value)
{
	GtkAdjustment	*adj;

	adj = gtk_adjustment_new(value, 1, 255, 1.0, 10.0, 0);
	*spin = gtk_spin_button_new(adj, 1.0, 0);
	gtk_entry_set_width_chars(GTK_ENTRY(*spin), 4);
	gtk_spin_button_set_numeric(GTK_SPIN_BUTTON(*spin), TRUE);
	gtk_widget_set_margin_top(*spin, 5);
	gtk_widget_set_margin_bottom(*spin, 5);
}

static void	gtk_set_filter_param_spinner(t_spinner *spinner, const char *label)
{
	spinner->label = gtk_label_new(label);
	gtk_widget_set_margin_start(spinner->label, 5);
	gtk_widget_set_margin_end(spinner->label, 5);
}

void		gtk_set_setting_filter_widgets(t_gtk_settings *settings, t_rt *rt)
{
	settings->filter_label = gtk_label_new("Filter:");
	gtk_widget_set_margin_end(settings->filter_label, 5);
	settings->filter_combo = gtk_combo_box_text_new();
	gtk_set_filters_list(GTK_COMBO_BOX_TEXT(settings->filter_combo));
	gtk_combo_box_set_active(GTK_COMBO_BOX(settings->filter_combo),
							rt->scene->filter);
	settings->v_filter_params = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	settings->h_blur = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_set_filter_param_spinner(&settings->blur_size, "Blur size:");
	gtk_set_spin_button_for_filter(&settings->blur_size.spin,
									rt->scene->filter_params.x);
	settings->h_sepia = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_set_filter_param_spinner(&settings->sepia_depth, "Sepia depth:");
	gtk_set_spin_button_for_filter(&settings->sepia_depth.spin,
									rt->scene->filter_params.y);
	settings->h_noise = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_set_filter_param_spinner(&settings->noise_depth, "Noise depth:");
	gtk_set_spin_button_for_filter(&settings->noise_depth.spin,
									rt->scene->filter_params.z);
}
