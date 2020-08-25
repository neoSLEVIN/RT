#include "serializer.h"

void	s_null(t_serializer *s)
{
	ft_printf("%[s", s->fd, "null");
}

void	s_bool(t_serializer *s, _Bool bool_value)
{
	ft_printf("%[s", s->fd, bool_value ? "true" : "false");
}

void	s_float(t_serializer *s, float num_value)
{
	ft_printf("%[.3f", s->fd, num_value);
}

void	s_int(t_serializer *s, int num_value)
{
	ft_printf("%[d", s->fd, num_value);
}
