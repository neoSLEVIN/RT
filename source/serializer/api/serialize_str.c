#include "serializer.h"

void	s_str(t_serializer *s, const char *str)
{
	ft_printf("%[s", s->fd, str ? str : "null");
}

void	s_str_free(t_serializer *s, char *str)
{
	s_str(s, str);
	if (str)
		ft_strdel(&str);
}

void	s_str_in_quotes(t_serializer *s, const char *str)
{
	if (str)
		ft_printf("%[c%s%c", s->fd, '"', str, '"');
	else
		s_null(s);
}

void	s_str_in_quotes_free(t_serializer *s, char *str)
{
	s_str_in_quotes(s, str);
	if (str)
		ft_strdel(&str);
}
