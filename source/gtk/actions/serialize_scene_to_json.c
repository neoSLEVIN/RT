#include "gtk_module.h"

gboolean	serialize_scene_to_json(gpointer data)
{
	t_rt	*rt;

	rt = (t_rt*)data;
	s_json_obj(rt->info->scene_filename, rt->scene);
	return (FALSE);
}
