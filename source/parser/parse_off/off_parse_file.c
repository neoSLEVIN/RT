#include "parser.h"
#include "ocl.h"

_Bool		off_check_format(t_off *off)
{
	char	*err_msg;

	err_msg = "First line must be \"OFF\"";
	if ((get_next_line(off->fd, &off->line)) <= 0)
		return (off_deinit(off, TRUE, err_msg));
	if (!off->line || !ft_strequ(off->line, "OFF"))
		return (off_deinit(off, TRUE, err_msg));
	(off->line) ? ft_strdel(&off->line) : 0;
	return (TRUE);
}

_Bool		off_parse_file(t_off *off, char *filename)
{
	char *fullPath;

	fullPath = ft_strjoin(OFF_PATH, filename);
	if (!off_init(off, fullPath))
		return (FALSE);
	if (!off_check_format(off))
		return (FALSE);
	if (!off_check_params(off))
		return (FALSE);
	off->points = (FLT3*)malloc(sizeof(FLT3) * off->p_cnt);
	off->faces = (cl_int3*)malloc(sizeof(cl_int3) * off->f_cnt);
	off->colors = (FLT3*)malloc(sizeof(FLT3) * off->f_cnt);
	if (!off->points || !off->faces || !off->colors)
		ft_error("Can't allocate memory");
	if (!off_check_vertices(off))
		return (FALSE);
	if (!off_check_faces(off))
		return (FALSE);
	if (get_next_line(off->fd, &off->line) != 0)
		return (off_deinit(off, TRUE, "Last line not empty"));
	return (off_deinit(off, FALSE, NULL));
}
