#include "gtk_module.h"

FLT2	get_angle_by_diff(INT2 diff, INT2 axis, INT2 screen_size)
{
	return ((FLT2){(cl_float)diff.x / screen_size.x * PI / 4 * axis.x,
					(cl_float)diff.y / screen_size.y * PI / 6 * axis.y});
}
