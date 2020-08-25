#include "serializer.h"

static void	s_filter_param(t_serializer *s, FLT3 params, FILTER filter)
{
	if (filter == BLUR)
	{
		s_comma(s);
		s_name(s, "blur size");
		s_int(s, (int)params.x);
	}
	else if (filter == SEPIA)
	{
		s_comma(s);
		s_name(s, "sepia depth");
		s_int(s, (int)params.y);
	}
	else if (filter == NOISE)
	{
		s_comma(s);
		s_name(s, "noise depth");
		s_int(s, (int)params.z);
	}
}

void		s_settings_obj(t_serializer *s, SCENE *scene)
{
	s_open_obj_with_name(s, "settings");
	s_name(s, "fps");
	s_float(s, scene->fps);
	s_comma(s);
	s_name(s, "filter");
	s_str_in_quotes_free(s, get_filter_type_name(scene->filter));
	s_filter_param(s, scene->filter_params, scene->filter);
	s_close_obj(s);
}
