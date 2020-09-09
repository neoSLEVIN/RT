/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sections.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:31:02 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:31:02 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void		init_default_shape_sections(DTO_SHAPE *dto)
{
	int	i;

	i = -1;
	dto->working_sections = 0;
	dto->is_complex_section = FALSE;
	while (++i < SECTION_CNT)
	{
		dto->sections[i].on = FALSE;
		dto->sections[i].type = PLANE;
		dto->sections[i].param = 1.0f;
		dto->sections[i].position = dto->transform.position;
		dto->sections[i].direction = (FLT3){0.0f, 1.0f, 0.0f};
	}
}

SECTION		parse_section_idx(const JC_FIELD parent, const size_t index,
							FLT3 dto_position)
{
	JC_FIELD	section_field;
	SECTION		section;

	section_field = jc_get_field_idx(parent, index, JC_OBJ);
	section.on = jc_get_bool_or_default(section_field, "on", TRUE);
	section.type = parse_section_type(section_field, "type");
	section.param = jc_get_float_or_default(section_field, "radius", 1.0f);
	if (section.param < 0.1f)
		parse_error(jc_full_name(section_field), "radius",
			"The value must be greater or equal than 0.1");
	section.position =
		parse_cl_float3_or_default(section_field, "position", dto_position);
	section.direction =
		parse_cl_float3_or_default(section_field, "direction",
			(FLT3){0.0f, 1.0f, 0.0f});
	section.direction = v3_norm(section.direction);
	if (v3_length(section.direction) == 0.0f)
		parse_error(jc_full_name(section_field), "direction",
			"The vector must not be a zero vector.");
	return (section);
}

_Bool		parse_section_style(const JC_FIELD parent, const char *child_name)
{
	char	*str_style;
	_Bool	is_complex;

	is_complex = FALSE;
	str_style = ft_str_to_upper(jc_get_string(parent, child_name, TRUE));
	if (str_style == NULL)
		return (FALSE);
	if (ft_strequ(str_style, "SIMPLE"))
		is_complex = FALSE;
	else if (ft_strequ(str_style, "COMPLEX"))
		is_complex = TRUE;
	else
		parse_error(jc_full_name(parent), child_name,
			"Incorrect style of sections.\n\t"
			"Allowed types: [SIMPLE, COMPLEX]");
	ft_strdel(&str_style);
	return (is_complex);
}

static void	parse_sections_loop(JC_FIELD sections_array_field, DTO_SHAPE *dto,
								int cnt)
{
	int	i;

	i = -1;
	while (++i < cnt)
	{
		dto->sections[i] =
			parse_section_idx(sections_array_field, i, dto->transform.position);
		if (dto->sections[i].on)
			++dto->working_sections;
	}
}

void		parse_sections(const JC_FIELD parent, const char *child_name,
							DTO_SHAPE *dto)
{
	JC_FIELD	sections_entity_field;
	JC_FIELD	sections_array_field;
	int			cnt;

	init_default_shape_sections(dto);
	sections_entity_field =
		jc_get_field(parent, child_name, (JC_OBJ | JC_NULL));
	if (jc_is_null(sections_entity_field))
		return ;
	dto->is_complex_section =
		parse_section_style(sections_entity_field, "style");
	sections_array_field =
		jc_get_field(sections_entity_field, "elements", (JC_ARR | JC_NULL));
	if (jc_is_null(sections_array_field))
		return ;
	cnt = jc_get_array_length(sections_array_field);
	if (cnt > SECTION_CNT)
		parse_error(jc_full_name(sections_array_field), NULL,
			"Max count of elements: 6");
	parse_sections_loop(sections_array_field, dto, cnt);
}
