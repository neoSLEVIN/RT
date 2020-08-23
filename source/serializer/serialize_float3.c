#include "serializer.h"

void	s_float3(t_serializer *s, FLT3 num_value)
{
	ft_printf("%[s[%.3f, %.3f, %.3f]", s->fd, "",
				num_value.x, num_value.y, num_value.z);
}
