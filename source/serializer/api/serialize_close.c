#include "serializer.h"

void	s_close_obj_no_indent(t_serializer *s)
{
	s_indent_dec(s);
	s_str(s, "}");
}

void	s_close_arr_no_indent(t_serializer *s)
{
	s_indent_dec(s);
	s_str(s, "]");
}

void	s_close_obj(t_serializer *s)
{
	s_indent_dec(s);
	s_indent(s);
	s_str(s, "}");
}

void	s_close_arr(t_serializer *s)
{
	s_indent_dec(s);
	s_indent(s);
	s_str(s, "]");
}
