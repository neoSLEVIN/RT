#include "gtk_module.h"

void	changing_filter_type(GtkComboBox *filter_combo, gpointer data)
{
	t_rt	*rt;
	cl_int	err;

	rt = (t_rt*)data;
	rt->scene->filter = gtk_combo_box_get_active(filter_combo);
	err = clSetKernelArg(rt->ocl->kernel, 10, sizeof(FILTER),
						rt->ocl->dto.filter);
	check_error_cl(err,"clSetKernelArg", "filter");
	draw_image(rt);
}
