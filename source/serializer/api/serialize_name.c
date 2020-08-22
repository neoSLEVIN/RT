#include "serializer.h"

void	s_name(t_serializer *s, const char *name)
{
	s_indent(s);
	ft_printf("%[s\"%s\": ", s->fd, "", name, '"');
}

void	s_open_obj_with_name(t_serializer *s, const char *name)
{
	s_name(s, name);
	s_str(s, "{");
	s_indent_inc(s);
}

void	s_open_arr_with_name(t_serializer *s, const char *name)
{
	s_name(s, name);
	s_str(s, "[");
	s_indent_inc(s);
}
