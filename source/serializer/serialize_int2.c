#include "serializer.h"

void	s_int2(t_serializer *s, INT2 num_value)
{
	ft_printf("%[s[%d, %d]", s->fd, "", num_value.x, num_value.y);
}
