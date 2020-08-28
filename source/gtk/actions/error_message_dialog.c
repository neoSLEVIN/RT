#include "gtk_module.h"

void	error_message_dialog(t_rt *rt, const char *filename, char **err)
{
	GtkWidget	*dialog;

	dialog = gtk_message_dialog_new(GTK_WINDOW(rt->gtk->window), 0,
									GTK_MESSAGE_ERROR,
									GTK_BUTTONS_CLOSE,
									"Error in file '%s':\n%s",
									filename, *err);
	gtk_window_set_title(GTK_WINDOW(dialog), "Error");
	gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy(dialog);
	ft_strdel(err);
}
