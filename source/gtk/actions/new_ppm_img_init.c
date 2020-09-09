/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_ppm_img_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:22:16 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:22:16 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

static char		*ppm_name_message_dialog(GtkWindow *window, _Bool is_another)
{
	GtkWidget	*dialog;
	GtkWidget	*box;
	char		*name;
	GtkWidget	*entry;

	dialog = gtk_message_dialog_new(window, 0,
									GTK_MESSAGE_QUESTION,
									GTK_BUTTONS_OK,
									"Enter %sPPM name:",
									is_another ? "another " : "");
	gtk_window_set_title(GTK_WINDOW(dialog), "PPM name");
	entry = gtk_entry_new();
	gtk_entry_set_max_length(GTK_ENTRY(entry), 20);
	box = gtk_bin_get_child(GTK_BIN(dialog));
	gtk_container_add(GTK_CONTAINER(GTK_BOX(box)), entry);
	gtk_widget_show_all(dialog);
	gtk_dialog_run(GTK_DIALOG(dialog));
	if (!(name = ft_strdup(gtk_entry_get_text(GTK_ENTRY(entry)))))
		ft_error("Can't allocate memory");
	gtk_widget_destroy(dialog);
	return (name);
}

static char		*get_ppm_name(GtkWindow *window, PPM_IMG *ppm,
								_Bool is_normal_map)
{
	char	*name;
	_Bool	another_try;

	name = NULL;
	another_try = FALSE;
	while (!name)
	{
		name = ppm_name_message_dialog(window, another_try);
		if (name && ft_strlen(name) != 0 &&
			check_for_texture_name(ppm, name, is_normal_map) == -101)
			break ;
		another_try = TRUE;
		ft_strdel(&name);
	}
	return (name);
}

static PPM_IMG	*new_ppm_img_init_base(char *filename, DTO_PPM_IMG *dto,
										char *name)
{
	PPM_IMG	*ppm_img;

	if ((ppm_img = (PPM_IMG*)malloc(sizeof(PPM_IMG))) == NULL)
		ft_error("Can't allocate memory");
	ppm_img->dto = dto;
	ppm_img->next = NULL;
	ppm_img->prev = NULL;
	ppm_img->path = filename;
	ppm_img->name = name;
	return (ppm_img);
}

PPM_IMG			*new_ppm_img_init(t_rt *rt, char *filename, PPM_IMG **ppm_list,
									_Bool is_normal_map)
{
	DTO_PPM_IMG	*dto;
	PPM_IMG		*new_ppm;
	PPM_IMG		*temp;
	char		*err;

	dto = NULL;
	err = NULL;
	if (!read_ppm_safe(filename, &dto, &err))
	{
		error_message_dialog(rt, filename, &err);
		return (NULL);
	}
	new_ppm = new_ppm_img_init_base(filename, dto,
		get_ppm_name(GTK_WINDOW(rt->gtk->window), *ppm_list, is_normal_map));
	if (*ppm_list == NULL)
	{
		*ppm_list = new_ppm;
		return (new_ppm);
	}
	temp = *ppm_list;
	while (temp->next)
		temp = temp->next;
	temp->next = new_ppm;
	new_ppm->prev = temp;
	return (new_ppm);
}
