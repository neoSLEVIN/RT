/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serialize_scene.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:32:17 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:32:18 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serializer.h"

void	s_scene_obj(t_serializer *s, SCENE *scene)
{
	s_open_obj_with_name(s, "scene");
	s_camera_obj(s, scene->cam.dto, &scene->cam);
	s_comma(s);
	s_lights_arr(s, scene->lights);
	s_comma(s);
	s_shapes_arr(s, scene->shapes, scene);
	s_comma(s);
	s_ppm_img_arr(s, "textures", scene->textures, TEXTURE_PATH);
	s_comma(s);
	s_ppm_img_arr(s, "normal maps", scene->normal_maps, NORMAL_MAP_PATH);
	s_close_obj(s);
}
