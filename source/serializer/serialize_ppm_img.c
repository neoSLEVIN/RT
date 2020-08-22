#include "serializer.h"

static char	*get_ppm_name_by_index(PPM_IMG *ppm, int index)
{
	int	i;

	if (index < 0)
		return (NULL);
	i = 0;
	while (ppm && i++ != index)
		ppm = ppm->next;
	if (!ppm)
		return (NULL);
	return (ppm->name);
}

void		s_shape_ppm_img_obj(t_serializer *s, int id, const char *name,
								PPM_IMG *ppm)
{
	s_open_obj_with_name(s, name);
	s_name(s, "name");
	s_str_in_quotes(s, get_ppm_name_by_index(ppm, id));
	s_close_obj(s);
}

static void	s_ppm_img_obj(t_serializer *s, PPM_IMG *ppm)
{
	s_open_obj(s);
	s_name(s, "name");
	s_str_in_quotes(s, ppm->name);
	s_comma(s);
	s_name(s, "path");
	s_str_in_quotes(s, ppm->path);
	s_close_obj(s);
}

void		s_ppm_img_arr(t_serializer *s, const char *name, PPM_IMG *ppm)
{
	s_open_arr_with_name(s, name);
	while (ppm)
	{
		s_ppm_img_obj(s, ppm);
		if (ppm->next)
			s_comma(s);
		ppm = ppm->next;
	}
	s_close_arr(s);
}
