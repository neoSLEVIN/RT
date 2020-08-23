#include "serializer.h"

void	s_scene_obj(t_serializer *s, SCENE *scene)
{
	s_open_obj_with_name(s, "scene");
	s_camera_obj(s, scene->cam.dto);
	s_comma(s);
	s_lights_arr(s, scene->lights);
	s_comma(s);
	s_shapes_arr(s, scene->shapes, scene->textures, scene->normal_maps);
	s_comma(s);
	s_ppm_img_arr(s, "textures", scene->textures);
	s_comma(s);
	s_ppm_img_arr(s, "normal maps", scene->normal_maps);
	s_close_obj(s);
}
