#include "parser.h"

int		parse_params(int fd, int *vertices_faces, char **err)
{
	char *line;

	if (get_next_line(fd, &line) == 0)
		return (error_safe(err, "gnl error2"));
	if (get_next_line(fd, &line) == 0)
		return (error_safe(err, "gnl error3"));
	return (set_params_from_line(line, vertices_faces, err));
}

float	**get_points(int points_cnt, int fd, char **err)
{
	float	**points;
	char	*line;
	int		i;

	i = 0;
	if ((points = (float**)malloc(sizeof(float*) * points_cnt)) == NULL)
		ft_error("Can't allocate memory");
	while (i < points_cnt)
	{
		if (get_next_line(fd, &line) == 0)
		{
			error_safe(err, "gnl error3");
			clear_points(points, i);
			return (NULL);
		}
		points[i] = get_points_from_line(line);
		i++;
	}
	return (points);
}

int		**get_faces(int faces_cnt, int fd, char **err)
{
	int		**faces;
	char	*line;
	int		i;

	i = 0;
	if ((faces = (int**)malloc(sizeof(int*) * faces_cnt)) == NULL)
		ft_error("Can't allocate memory");
	while (i < faces_cnt)
	{
		if (get_next_line(fd, &line) == 0)
		{
			error_safe(err, "gnl error3");
			clear_faces(faces, i);
			return (NULL);
		}
		faces[i] = get_faces_from_line(line);
		i++;
	}
	return (faces);
}

FLT3	get_point(float **points, int position)
{
	float one;
	float two;
	float three;

	one = points[position][0];
	two = points[position][1];
	three = points[position][2];
	return (FLT3){one, two, three};
}

void	set_triangle_points(DTO_SHAPE *dto, float **points, int **faces, int i)
{
	dto->transform.dots[0] = get_point(points, faces[i][1]);
	dto->transform.dots[1] = get_point(points, faces[i][2]);
	dto->transform.dots[2] = get_point(points, faces[i][3]);
	dto->transform.position =
	v3_scale(v3_add(v3_add(dto->transform.dots[0], dto->transform.dots[1]),
					dto->transform.dots[2]), 1.0f / 3.0f);
}
