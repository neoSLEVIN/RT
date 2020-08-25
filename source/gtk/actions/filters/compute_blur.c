#include "gtk_module.h"

static void	init_blur(t_blur *blur, unsigned segment_size)
{
	blur->average = (cl_uint3){0, 0, 0};
	blur->segment_size = segment_size;
	blur->count_of_segments.x = (COLS % blur->segment_size == 0) ?
		(COLS / blur->segment_size) : (COLS / blur->segment_size + 1);
	blur->count_of_segments.y = (ROWS % blur->segment_size == 0) ?
		(ROWS / blur->segment_size) : (ROWS / blur->segment_size + 1);
	blur->segment = (cl_int2){-1, -1};
	blur->pix_of_segment = (cl_int2){-1, -1};
	blur->pix = -1;
}

static void	segment_loop(void (*action_for_pixel)(cl_uchar4 *, cl_uint3 *),
					cl_uchar4 *buffer, t_blur *blur)
{
	cl_int2	segment_start;

	segment_start.y = blur->segment.y * blur->segment_size;
	segment_start.x = blur->segment.x * blur->segment_size;
	blur->pix_of_segment.y = -1;
	while (++blur->pix_of_segment.y < blur->segment_size &&
			(segment_start.y + blur->pix_of_segment.y) < ROWS)
	{
		blur->pix_of_segment.x = 0;
		blur->pix =
			(segment_start.y + blur->pix_of_segment.y) * COLS + segment_start.x;
		while (blur->pix_of_segment.x < blur->segment_size &&
				(segment_start.x + blur->pix_of_segment.x) < COLS)
		{
			action_for_pixel(&buffer[blur->pix], &blur->average);
			++blur->pix_of_segment.x;
			++blur->pix;
		}
	}
}

void		compute_blur(t_rt *rt)
{
	cl_uchar4	*buffer;
	t_blur		blur;

	buffer = rt->ocl->dto.buffer;
	init_blur(&blur, (unsigned)rt->scene->filter_params.x);
	while (++blur.segment.y < blur.count_of_segments.y)
	{
		blur.segment.x = -1;
		while (++blur.segment.x < blur.count_of_segments.x)
		{
			blur.average = (cl_uint3){0, 0, 0};
			segment_loop(put_pixel_to_average_sum, buffer, &blur);
			blur.average =
				get_average_from_sum(&blur.average,
					blur.pix_of_segment.y * blur.pix_of_segment.x);
			segment_loop(put_average_to_pixel, buffer, &blur);
		}
	}
}
