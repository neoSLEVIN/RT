#include "parser.h"

SHAPE	*parse_triangle(const char *filename, int *cnt, DTO_CAM *cam,
						char **err)
{
	if (check_file_off(filename, err))
		return (NULL);
	return (get_triangles(filename, cnt, cam, err));
}

SHAPE	*get_triangles(const char *filename, int *cnt, DTO_CAM *cam, char **err)
{
	int		fd;
	int		vertices_faces[2];
	float	**points;
	int		**faces;

	if ((fd = open(filename, O_RDONLY)) < 0)
	{
		error_safe(err, "fd open error");
		return (NULL);
	}
	if (parse_params(fd, vertices_faces, err))
		return (NULL);
	if ((points = get_points(vertices_faces[0], fd, err)) == NULL)
		return (NULL);
	if ((faces = get_faces(vertices_faces[1], fd, err)) == NULL)
		return (NULL);
	*cnt = vertices_faces[1];
	return (build_triangles(points, faces, vertices_faces[1], cam));
}

SHAPE	*build_triangles(float **points, int **faces, int triangle_cnt,
						DTO_CAM *cam)
{
	SHAPE	*shapes;
	SHAPE	*temp_shape;
	int		i;

	shapes = create_triangle(points, faces, cam, 0);
	temp_shape = shapes;
	i = 1;
	while (i < triangle_cnt)
	{
		temp_shape->next = create_triangle(points, faces, cam, i);
		temp_shape->next->prev = temp_shape;
		temp_shape = temp_shape->next;
		i++;
	}
	return (shapes);
}

SHAPE	*create_triangle(float **points, int **faces, DTO_CAM *cam,
						int position)
{
	SHAPE		*tr;
	DTO_SHAPE	*dto;

	if ((tr = (SHAPE*)malloc(sizeof(SHAPE))) == NULL)
		ft_error("Can't allocate memory");
	if ((dto = (DTO_SHAPE*)malloc(sizeof(DTO_SHAPE))) == NULL)
		ft_error("Can't allocate memory");
	get_default_shape(tr, dto);
	init_default_shape_dto(cam, tr->dto);
	tr->dto->type = TRIANGLE;
	set_triangle_points(tr->dto, points, faces, position);
	return (tr);
}
