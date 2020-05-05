/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_standard_shapes.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 00:31:20 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/05 07:37:29 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	*parse_plane(const JC_FIELD shape_field)
{
	t_plane	*plane;

	if(!(plane = (t_plane*)malloc(sizeof(t_plane))))
		ft_error("Can't allocate memory");
	plane->type = PLANE;
	plane->transform = parse_transform(shape_field, "transform");
	plane->material = parse_material(shape_field, "material");
	return (plane);
}

void	*parse_sphere(const JC_FIELD shape_field)
{
	t_sphere	*sphere;

	if(!(sphere = (t_sphere*)malloc(sizeof(t_sphere))))
		ft_error("Can't allocate memory");
	sphere->type = SPHERE;
	sphere->transform = parse_transform(shape_field, "transform");
	sphere->material = parse_material(shape_field, "material");
	sphere->radius = jc_get_float(shape_field, "radius");
	if (sphere->radius <= 0.0f)
		parse_error(jc_full_name(shape_field), "radius",
					" Value must be positive.");
	return (sphere);
}

void	*parse_cylinder(const JC_FIELD shape_field)
{
	t_cylinder	*cylinder;

	if(!(cylinder = (t_cylinder*)malloc(sizeof(t_cylinder))))
		ft_error("Can't allocate memory");
	cylinder->type = CYLINDER;
	cylinder->transform = parse_transform(shape_field, "transform");
	cylinder->material = parse_material(shape_field, "material");
	cylinder->radius = jc_get_float(shape_field, "radius");
	if (cylinder->radius <= 0.0f)
		parse_error(jc_full_name(shape_field), "radius",
					" Value must be positive.");
	return (cylinder);
}

void	*parse_cone(const JC_FIELD shape_field)
{
	t_cone	*cone;

	if(!(cone = (t_cone*)malloc(sizeof(t_cone))))
		ft_error("Can't allocate memory");
	cone->type = CONE;
	cone->transform = parse_transform(shape_field, "transform");
	cone->material = parse_material(shape_field, "material");
	cone->angle = jc_get_float(shape_field, "angle");
	if (cone->angle <= 0.0f || cone->angle >= 180.0f)
		parse_error(jc_full_name(shape_field), "angle",
					" Value must be in range (0.0; 180.0).");
	return (cone);
}
