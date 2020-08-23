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

static void	change_folder(char **folder, GtkWidget *dialog)
{
	char	*new_folder;

	new_folder = gtk_file_chooser_get_current_folder(GTK_FILE_CHOOSER(dialog));
	if (ft_strequ(*folder, new_folder))
		g_free(new_folder);
	else
	{
		if (*folder)
			g_free(*folder);
		*folder = new_folder;
	}
}

_Bool		get_new_file_name(char **filename, char **folder,
							char *default_name)
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
	if (*folder)
		gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(dialog), *folder);
	gtk_file_chooser_set_current_name(GTK_FILE_CHOOSER(dialog), default_name);
	if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT)
	{
		change_filename(filename, dialog);
		change_folder(folder, dialog);
		gtk_widget_destroy(dialog);
		return (TRUE);
	}
	gtk_widget_destroy(dialog);
	return (FALSE);
}
