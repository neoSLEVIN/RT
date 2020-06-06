/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_shape.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/27 03:28:29 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char		*unnamed_shape(size_t index)
{
	char	*name;
	char	*str_index;

	if (!(str_index = ft_itoa((int)index)))
		ft_error("Can't allocate memory");
	if (!(name = ft_strnew(ft_strlen("Unnamed_") + ft_strlen(str_index))))
		ft_error("Can't allocate memory");
	ft_strcpy(name, "Unnamed_");
	ft_strcat(name, str_index);
	ft_strdel(&str_index);
	return (name);
}

static float	parse_shape_param_by_type(const JC_FIELD shape_field,
										SHAPE_TYPE type)
{
	float	param;

	if (type == PLANE)
		param = 0.0f;
	else if (type == SPHERE || type == CYLINDER || type == CAPPEDCYLINDER)
	{
		param = jc_get_float(shape_field, "radius");
		if (param < 0.1f)
			parse_error(jc_full_name(shape_field), "radius",
				"The value must be greater or equal than 0.1");
	}
	else if (type == CONE)
	{
		param = jc_get_float(shape_field, "angle");
		if (param < 1.0f || param > 89.0f)
			parse_error(jc_full_name(shape_field), "angle",
				"Value must be in range [1.0; 89.0].");
		param = deg_to_rad(param);
	}
	else
		ft_error("Unknown action");
	return (param);
}

static void		init_default_shape_params(SHAPE *shape)
{
	shape->prev = NULL;
	shape->next = NULL;
	shape->widgets = NULL;
	shape->tree_iter = NULL;
	shape->dto->marker = FALSE;
	shape->texture_name = NULL;
}

//TODO maybe parse section
void			init_default_shape_section(SHAPE *shape)
{
	shape->dto->working_sections = 6;
	shape->dto->is_complex_section = FALSE;
	shape->dto->section[0].type = SPHERE;
	shape->dto->section[1].type = PLANE;
	shape->dto->section[2].type = PLANE;
	shape->dto->section[3].type = PLANE;
	shape->dto->section[4].type = PLANE;
	shape->dto->section[5].type = PLANE;
	shape->dto->section[0].on = FALSE;
	shape->dto->section[1].on = TRUE;
	shape->dto->section[2].on = TRUE;
	shape->dto->section[3].on = TRUE;
	shape->dto->section[4].on = FALSE;
	shape->dto->section[5].on = FALSE;
	shape->dto->section[0].param = shape->dto->param - 10.0f;
	shape->dto->section[1].param = shape->dto->param - 10.0f;
	shape->dto->section[2].param = shape->dto->param - 10.0f;
	shape->dto->section[3].param = shape->dto->param - 10.0f;
	shape->dto->section[4].param = shape->dto->param - 10.0f;
	shape->dto->section[5].param = shape->dto->param - 10.0f;
	shape->dto->section[0].transform.position = shape->dto->transform.position;
	shape->dto->section[1].transform.position = shape->dto->transform.position;
	shape->dto->section[2].transform.position = shape->dto->transform.position;
	shape->dto->section[3].transform.position = shape->dto->transform.position;
	shape->dto->section[4].transform.position = shape->dto->transform.position;
	shape->dto->section[5].transform.position = shape->dto->transform.position;
	shape->dto->section[0].transform.direction = (FLT3){1.0f, 0.0f, 0.0f};
	shape->dto->section[1].transform.direction = (FLT3){0.0f, 1.0f, 0.0f};
	shape->dto->section[2].transform.direction = (FLT3){0.0f, 0.0f, 1.0f};
	shape->dto->section[3].transform.direction = (FLT3){1.0f, 0.0f, 0.0f};
	shape->dto->section[4].transform.direction = (FLT3){1.0f, 1.0f, 0.0f};
	shape->dto->section[5].transform.direction = (FLT3){0.0f, 1.0f, 1.0f};
}

SHAPE			*parse_shape_idx(const JC_FIELD parent, const size_t index,
								PPM_IMG *textures)
{
	JC_FIELD	shape_field;
	SHAPE		*shape;
	size_t		length;

	shape_field = jc_get_field_idx(parent, index, JC_OBJ);
	shape = (SHAPE*)malloc(sizeof(SHAPE));
	if (!shape || !(shape->dto = (DTO_SHAPE*)malloc(sizeof(DTO_SHAPE))))
		ft_error("Can't allocate memory");
	init_default_shape_params(shape);
	shape->name = jc_get_string(shape_field, "name", TRUE);
	if (!shape->name)
		shape->name = unnamed_shape(index);
	length = ft_strlen(shape->name);
	if (length == 0 || length > 20)
		parse_error(jc_full_name(shape_field), "name",
			"The field length must be in the range (0; 20].");
	shape->dto->type = parse_shape_type(shape_field, "type");
	shape->dto->param =
		parse_shape_param_by_type(shape_field, shape->dto->type);
	shape->dto->transform = parse_transform(shape_field, "transform");
	shape->dto->material = parse_material(shape_field, "material");
	shape->dto->texture = parse_texture_info_in_shape(shape_field, "texture",
		&shape->texture_name, textures);
	init_default_shape_section(shape);
	return (shape);
}

SHAPE			*parse_shapes(const JC_FIELD parent, const char *child_name,
							PPM_IMG *textures)
{
	JC_FIELD	shapes_field;
	SHAPE		*shapes;
	SHAPE		*temp_shape;
	size_t		length;
	size_t		i;

	shapes_field = jc_get_field(parent, child_name, (JC_ARR | JC_NULL));
	if (jc_is_null(shapes_field))
		return (NULL);
	length = jc_get_array_length(shapes_field);
	if (length == 0)
		return (NULL);
	shapes = parse_shape_idx(shapes_field, 0, textures);
	temp_shape = shapes;
	i = 0;
	while (++i < length)
	{
		temp_shape->next = parse_shape_idx(shapes_field, i, textures);
		temp_shape->next->prev = temp_shape;
		temp_shape = temp_shape->next;
	}
	return (shapes);
}
