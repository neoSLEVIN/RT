#include "serializer.h"

void	s_settings_obj(t_serializer *s, SCENE *scene)
{
	s_open_obj_with_name(s, "settings");
	s_name(s, "fps");
	s_float(s, scene->fps);
	s_comma(s);
	s_name(s, "filter");
	s_str_in_quotes_free(s, get_filter_type_name(scene->filter));
	s_close_obj(s);
}
