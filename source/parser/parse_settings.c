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

FILTER	parse_filter_type(const JC_FIELD parent, const char *child_name)
{
	char		*str_type;
	FILTER		filter;
	
	filter = NO_FILTER;
	str_type = ft_str_to_upper(jc_get_string_or_default(parent, child_name, "NO FILTERS"));
	if (ft_strequ(str_type, "SEPIA"))
		filter = SEPIA;
	else if (ft_strequ(str_type, "NEGATIVE"))
		filter = NEGATIVE;
	else if (ft_strequ(str_type, "NOISE"))
		filter = NOISE;
	else if (ft_strequ(str_type, "SHADES OF GRAY"))
		filter = SHADES_OF_GRAY;
	else if (ft_strequ(str_type, "NO FILTERS"))
		filter = NO_FILTER;
	else
		parse_error(jc_full_name(parent), child_name,
			"Incorrect type of filter.\n\t"
			"Allowed types: [SEPIA, NEGATIVE, NOISE, SHADES OF GRAY]");
	ft_strdel(&str_type);
	return (filter);
}

static void	default_settings(SCENE *scene)
{
	scene->fps = 25.0f;
	scene->filter = NO_FILTER;
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
	scene->filter = parse_filter_type(settings_field, "filter");
}
