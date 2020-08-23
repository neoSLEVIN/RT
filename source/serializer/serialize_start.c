#include "serializer.h"

void	s_json_obj(const char *scene_filename, SCENE *scene)
{
	t_serializer	s;

	s_open_serializer(&s, scene_filename);
	s_open_obj_no_indent(&s);
	s_settings_obj(&s, scene);
	s_comma(&s);
	s_scene_obj(&s, scene);
	s_close_obj(&s);
	s_close_serializer(&s);
}
