#include "gtk_module.h"

static void	change_filename(char **filename, GtkWidget *dialog)
{
	char	*new_filename;

	new_filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
	if (ft_strequ(*filename, new_filename))
		g_free(new_filename);
	else
	{
		if (*filename)
			g_free(*filename);
		*filename = new_filename;
	}
}

_Bool		get_new_file_name(char **filename)
{
	GtkWidget	*dialog;
	GtkWidget	*window;

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	dialog = gtk_file_chooser_dialog_new("Save File", (GtkWindow*)window,
								GTK_FILE_CHOOSER_ACTION_SAVE,
								"_Cancel", GTK_RESPONSE_CANCEL,
								"_Open", GTK_RESPONSE_ACCEPT,
								NULL);
	gtk_file_chooser_set_do_overwrite_confirmation(GTK_FILE_CHOOSER(dialog),
													TRUE);
	if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT)
	{
		change_filename(filename, dialog);
		gtk_widget_destroy(dialog);
		return (TRUE);
	}
	gtk_widget_destroy(dialog);
	return (FALSE);
}
