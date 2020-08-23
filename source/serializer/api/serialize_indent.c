#include "serializer.h"

void	s_indent_inc(t_serializer *s)
{
	++s->indents;
}

void	s_indent_dec(t_serializer *s)
{
	if (s->indents > 0)
		--s->indents;
}

void	s_indent(t_serializer *s)
{
	int	i;

	i = -1;
	s_str(s, "\n");
	while (++i < s->indents)
		ft_printf("%[s", s->fd, "  ");
}
