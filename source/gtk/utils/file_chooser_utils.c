/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_chooser_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/13 14:46:42 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/13 14:46:51 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

static _Bool	is_subdir(const char *dir_name, const char *subdir_name)
{
	DIR		*subdir;
	char	*subdir_path;

	if (ft_strequ(subdir_name, ".") || ft_strequ(subdir_name, ".."))
		return (TRUE);
	if (!(subdir_path = ft_strjoin(dir_name, subdir_name)))
		ft_error("Can't allocate memory");
	subdir = opendir(subdir_path);
	ft_strdel(&subdir_path);
	if (subdir)
	{
		closedir(subdir);
		return (TRUE);
	}
	return (FALSE);
}

static void		gtk_set_files_list(t_chooser *ch, const char *dir_name,
									_Bool with_entry)
{
	DIR				*dir;
	struct dirent	*iter;

	if ((dir = opendir(dir_name)))
	{
		if (with_entry)
		{
			gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(ch->list),
										"New file");
			if (!(ch->files[ch->cnt++] = ft_strdup("New file")))
				ft_error("Can't allocate memory");
		}
		while ((iter = readdir(dir)) != NULL && ch->cnt < 100)
		{
			if (!is_subdir(dir_name, iter->d_name))
			{
				gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(ch->list),
											iter->d_name);
				if (!(ch->files[ch->cnt++] = ft_strdup(iter->d_name)))
					ft_error("Can't allocate memory");
			}
		}
		closedir(dir);
	}
}

void			init_chooser(t_chooser *chooser, const char *dir_path,
							_Bool with_entry, const char *default_name)
{
	chooser->cnt = 0;
	chooser->with_entry = with_entry;
	chooser->grid = gtk_grid_new();
	chooser->list = gtk_combo_box_text_new();
	gtk_widget_set_margin_end(chooser->list, 5);
	gtk_widget_set_margin_top(chooser->list, 5);
	gtk_widget_set_margin_bottom(chooser->list, 5);
	gtk_widget_set_margin_start(chooser->list, 5);
	gtk_set_files_list(chooser, dir_path, with_entry);
	if (with_entry || chooser->cnt > 0)
		gtk_combo_box_set_active(GTK_COMBO_BOX(chooser->list), 0);
	gtk_grid_attach(GTK_GRID(chooser->grid), chooser->list, 0, 0, 1, 1);
	if (with_entry)
	{
		chooser->entry = gtk_entry_new();
		gtk_entry_set_text(GTK_ENTRY(chooser->entry),
						default_name ? default_name : "default");
		gtk_entry_set_max_length(GTK_ENTRY(chooser->entry), 30);
		gtk_widget_set_margin_end(chooser->entry, 5);
		gtk_widget_set_margin_top(chooser->entry, 5);
		gtk_widget_set_margin_bottom(chooser->entry, 5);
		gtk_widget_set_margin_start(chooser->entry, 5);
		gtk_grid_attach_next_to(GTK_GRID(chooser->grid), chooser->entry,
								chooser->list, GTK_POS_BOTTOM, 1, 1);
	}
}

_Bool			deinit_chooser(t_chooser *chooser, _Bool res)
{
	int	i;

	i = -1;
	while (++i < chooser->cnt)
		(chooser->files[i]) ? ft_strdel(&chooser->files[i]) : 0;
	gtk_widget_destroy(chooser->dialog);
	return (res);
}

void			init_dialog(GtkWindow *window, t_chooser *chooser,
							const char *msg, const char *title)
{
	chooser->dialog = gtk_message_dialog_new(window, 0,
											GTK_MESSAGE_QUESTION,
											GTK_BUTTONS_OK,
											"%s", msg);
	gtk_window_set_title(GTK_WINDOW(chooser->dialog), title);
	gtk_window_set_position(GTK_WINDOW(chooser->dialog), GTK_WIN_POS_CENTER);
	gtk_window_set_resizable(GTK_WINDOW(chooser->dialog), FALSE);
	chooser->box = gtk_bin_get_child(GTK_BIN(chooser->dialog));
	gtk_container_add(GTK_CONTAINER(GTK_BOX(chooser->box)), chooser->grid);
	gtk_widget_show_all(chooser->dialog);
}
