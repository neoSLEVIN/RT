/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_settings.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 02:37:49 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/12 02:37:49 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	default_settings(SCENE *scene)
{
	scene->fps = 25.0f;
}

void parse_settings(JC_FIELD json_field, SCENE *scene)
{
	JC_FIELD	settings_field;

	settings_field = jc_get_field(json_field, "settings", (JC_OBJ | JC_NULL));
	if (jc_is_null(settings_field))
		return (default_settings(scene));
	scene->fps = jc_get_float_or_default(settings_field, "fps", 25);
	if (scene->fps < 0.5 || scene->fps > 80)
		parse_error(jc_full_name(settings_field), "fps",
					"Value must be in range [0.5; 80.0].");
}
