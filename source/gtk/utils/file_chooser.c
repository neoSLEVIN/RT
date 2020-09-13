/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_chooser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/13 14:46:47 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/13 14:46:50 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

_Bool		choose_file_name(GtkWindow *window, char **filename,
								const char *dir_path)
{
	t_chooser	chooser;
	int			index;
	char		*msg;

	init_chooser(&chooser, dir_path, FALSE, NULL);
	msg = (chooser.cnt) ? "Choose file:" : "No files";
	init_dialog(window, &chooser, msg, "Choose file");
	if (!chooser.with_entry && chooser.cnt == 0)
		gtk_widget_set_visible(chooser.list, FALSE);
	if (gtk_dialog_run(GTK_DIALOG(chooser.dialog)) == GTK_RESPONSE_OK &&
		chooser.cnt > 0)
	{
		index = gtk_combo_box_get_active(GTK_COMBO_BOX(chooser.list));
		if (!(*filename = ft_strjoin(dir_path, chooser.files[index])))
			ft_error("Can't allocate memory");
		return (deinit_chooser(&chooser, TRUE));
	}
	return (deinit_chooser(&chooser, FALSE));
}

static void	changing_filename(GtkComboBox *list, gpointer data)
{
	t_chooser	*chooser;
	int			index;

	chooser = (t_chooser*)data;
	index = gtk_combo_box_get_active(list);
	gtk_widget_set_visible(chooser->entry, index == 0);
}

_Bool		save_file_name(GtkWindow *window, char **filename,
						const char *dir_path, const char *default_name)
{
	t_chooser	chooser;
	int			index;
	const gchar	*temp;

	init_chooser(&chooser, dir_path, TRUE, default_name);
	init_dialog(window, &chooser, "Save file:", "Save file");
	g_signal_connect(G_OBJECT(chooser.list),
		"changed", G_CALLBACK(changing_filename), &chooser);
	if (gtk_dialog_run(GTK_DIALOG(chooser.dialog)) == GTK_RESPONSE_OK)
	{
		index = gtk_combo_box_get_active(GTK_COMBO_BOX(chooser.list));
		if (index == 0)
		{
			temp = gtk_entry_get_text(GTK_ENTRY(chooser.entry));
			if (!temp || ft_strlen_rus((const char *)temp) == 0)
				return (deinit_chooser(&chooser, FALSE));
			if (!(*filename = ft_strjoin(dir_path, temp)))
				ft_error("Can't allocate memory");
			return (deinit_chooser(&chooser, TRUE));
		}
		if (!(*filename = ft_strjoin(dir_path, chooser.files[index])))
			ft_error("Can't allocate memory");
		return (deinit_chooser(&chooser, TRUE));
	}
	return (deinit_chooser(&chooser, FALSE));
}
