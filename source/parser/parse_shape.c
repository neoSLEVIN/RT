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

static void		init_default_shape_params(SHAPE *shape)
{
	shape->prev = NULL;
	shape->next = NULL;
	shape->tree_iter = NULL;
	shape->dto->marker = FALSE;
	shape->texture_name = NULL;
	shape->normal_map_name = NULL;
}

static void		parse_shape_name(const JC_FIELD shape_field,
								const size_t index, SHAPE *shape)
{
	size_t	length;

	shape->name = jc_get_string(shape_field, "name", TRUE);
	(!shape->name) ? shape->name = unnamed_obj(index + 1, NULL) : 0;
	if ((length = ft_strlen_rus(shape->name)) == 0 || length > 20)
		parse_error(jc_full_name(shape_field), "name",
					"The field length must be in the range (0; 20].");
}

static void		parse_off(const JC_FIELD shape_field, SHAPE_TYPE type,
						t_off *off)
{
	char	*path;
	char	*dir;
	char	*file;

	if (type != OFF)
		return ;
	dir = OFF_PATH;
	file = jc_get_string(shape_field, "path", FALSE);
	if (!(path = ft_strjoin(dir, file)))
		ft_error("Can't allocate memory");
	ft_strdel(&file);
	if (!off_parse_file(off, path))
		parse_error(jc_full_name(shape_field), "path", off->err);
}

SHAPE			*parse_shape_idx(const JC_FIELD parent, const size_t index,
								SCENE *scene)
{
	JC_FIELD	shape_field;
	SHAPE		*shape;

	shape_field = jc_get_field_idx(parent, index, JC_OBJ);
	shape = (SHAPE*)malloc(sizeof(SHAPE));
	if (!shape || !(shape->dto = (DTO_SHAPE*)malloc(sizeof(DTO_SHAPE))))
		ft_error("Can't allocate memory");
	init_default_shape_params(shape);
	parse_shape_name(shape_field, index, shape);
	shape->dto->type = parse_shape_type(shape_field, "type");
	if (shape->dto->type == OFF && scene->off.filename)
		parse_error(jc_full_name(shape_field), "type",
				"Maximum one OFF shape in scene");
	parse_off(shape_field, shape->dto->type, &scene->off);
	parse_shape_param_by_type(shape_field, shape->dto->type,
							&shape->dto->params);
	shape->dto->transform =
			parse_transform(shape_field, "transform", shape->dto->type);
	shape->dto->material = parse_material(shape_field, "material");
	shape->dto->texture = parse_texture_info_in_shape(shape_field, "texture",
		&shape->texture_name, scene->textures);
	shape->dto->normal_map = parse_texture_info_in_shape(shape_field,
		"normal map", &shape->normal_map_name, scene->normal_maps);
	parse_sections(shape_field, "sections", shape->dto);
	return (shape);
}

SHAPE			*parse_shapes(const JC_FIELD parent, const char *child_name,
							SCENE *scene)
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
	shapes = parse_shape_idx(shapes_field, 0, scene);
	temp_shape = shapes;
	i = 0;
	while (++i < length)
	{
		temp_shape->next =
			parse_shape_idx(shapes_field, i, scene);
		temp_shape->next->prev = temp_shape;
		temp_shape = temp_shape->next;
	}
	return (shapes);
}
