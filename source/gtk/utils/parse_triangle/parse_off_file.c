//
//  parse_triangle.c
//  RT
//
//  Created by Babette Alvyn on 9/5/20.
//  Copyright © 2020 Babette Alvyn. All rights reserved.
//

#include "gtk_module.h"

SHAPE *get_triangles(const char *filename, int *cnt, DTO_CAM *cam, char **err);

SHAPE *parse_triangle(const char *filename, int *cnt, DTO_CAM *cam, char **err) {
    if (check_file_off(filename, err))
        return (NULL);
    return (get_triangles(filename, cnt, cam, err));
}

FLT3 get_point(float **points, int position) {
    float one;
    float two;
    float three;
    
    one = points[position][0];
    two = points[position][1];
    three = points[position][2];
    return (FLT3){one, two, three};
}

void set_points(DTO_SHAPE *dto, float **points, int **faces, int i) {
    int first_point_position = faces[i][1];
    int second_point_position = faces[i][2];
    int third_point_position = faces[i][3];
    dto->transform.dots[0] = get_point(points, first_point_position);
    dto->transform.dots[0] = get_point(points, second_point_position);
    dto->transform.dots[0] = get_point(points, third_point_position);
    dto->transform.position =
    v3_scale(v3_add(v3_add(dto->transform.dots[0], dto->transform.dots[1]), dto->transform.dots[2]),
            1.0f / 3.0f);
}

SHAPE *build_triangles(float **points, int **faces, int triangle_cnt, DTO_CAM *cam) {
    SHAPE *triangles;
    DTO_SHAPE *dto;
    int i;
    
    i = 0;
    if ((triangles = (SHAPE*)malloc(sizeof(SHAPE) * triangle_cnt)) == NULL)
        ft_error("Can't allocate memory");
    while (i < triangle_cnt) {
        if ((dto = (DTO_SHAPE*)malloc(sizeof(DTO_SHAPE))) == NULL)
            ft_error("Can't allocate memory");
        get_default_shape(triangles + i, dto);
        init_default_shape_dto(cam, triangles[i].dto);
        set_points(triangles[i].dto, points, faces, i);
        i++;
    }
    i = 0;
    while (i < triangle_cnt - 1) {
        triangles[i].next = triangles + (i + 1);
        i++;
    }
    return triangles;
}

SHAPE *get_triangles(const char *filename, int *cnt, DTO_CAM *cam, char **err) {
    int fd;
    int vertices_faces[2];
    float **points;
    int **faces;
    
    fd = open(filename, O_RDONLY);
    if (parse_params(fd, vertices_faces, err))
        return (NULL);
    if ((points = get_points(vertices_faces[0], fd, err)) == NULL)
        return (NULL);
    if ((faces = get_faces(vertices_faces[1], fd, err)) == NULL)
        return (NULL);
    *cnt = vertices_faces[1];
    return (build_triangles(points, faces, vertices_faces[1], cam));
}
