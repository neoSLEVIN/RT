//
//  parse_triangle.c
//  RT
//
//  Created by Babette Alvyn on 9/5/20.
//  Copyright © 2020 Babette Alvyn. All rights reserved.
//

#include "gtk_module.h"

int common_check_off(int fd, char **err);
int check_params(int fd, int *params, char **err);
int check_params_count(char **splits, int count, char **err);
int check_format(int fd, char **err);
void free_splits(char **splits, int count);
int check_element_count(char *line, int count, char **err);
int check_vertices(int fd, int *params, char **err);
int check_faces(int fd, int *params, char **err);


int    error_safe(char **err, const char *text)
{
    if (!(*err = ft_strdup(text)))
        ft_error("Can't allocate memory");
    return (1);
}


int check_file_off(const char *filename, char **err) {
    int fd;
    
    fd = open(filename, O_RDONLY);
    if (common_check_off(fd, err)) {
        close(fd);
        return (1);
    }
    close(fd);
    return (0);
}

SHAPE *parse_triangle(const char *filename, int *cnt, DTO_CAM *cam, char **err) {
    
    if (check_file_off(filename, err))
        return (NULL);
    
    
    
    
    
}


float *get_points_from_line(char *line) {
    char **splits;
    float *res;
    int i;
    
    i = 0;
    if ((splits = ft_strsplit(line, 32)) == NULL)
        ft_error("get points splits empty");
    if ((res = (float*)malloc(sizeof(float) * 3)) == NULL)
        ft_error("Can't allocate memory");
    while (i < 3) {
        res[i] = atof(splits[i]);
        i++;
    }
    return (res);
}

int *get_faces_from_line(char *line) {
    char **splits;
    int *res;
    int i;
    
    i = 0;
    splits = ft_strsplit(line, 32);
    if ((res = (int*)malloc(sizeof(int) * 4)) == NULL)
        ft_error("Can't allocate memory");
    while (i < 4) {
        res[i] = ft_atoi(splits[i]);
        i++;
    }
    return (res);
}

int set_params_from_line(char *line, int *vertices_faces, char **err) {
    char **splits;
    int i;
    
    i = 0;
    if ((splits = ft_strsplit(line, 32)) == NULL)
        return error_safe(err, "set_params_from_line NULL");
    while (i < 2) {
        vertices_faces[i] = ft_atoi(splits[i]);
        i++;
    }
    return (0);
}

int parse_params(int fd, int *vertices_faces, char **err) {
    char *line;
    
    if (get_next_line(fd, &line) == 0)
        return error_safe(err, "gnl error2");
    if (get_next_line(fd, &line) == 0)
        return error_safe(err, "gnl error3");
    return (set_params_from_line(line, vertices_faces, err));
}

void clear_points(float **points, int points_cnt) {
    int i;
    
    i = 0;
    while (i < points_cnt) {
        free(points[i]);
        i++;
    }
    free(points);
}

void clear_faces(int **points, int points_cnt) {
    int i;
    
    i = 0;
    while (i < points_cnt) {
        free(points[i]);
        i++;
    }
    free(points);
}


float** get_points(int points_cnt, int fd, char **err) {
    float **points;
    char *line;
    int i;
    
    i = 0;
    if ((points = (float**)malloc(sizeof(float*) * points_cnt)) == NULL)
        ft_error("Can't allocate memory");
    while (i < points_cnt) {
        if (get_next_line(fd, &line) == 0) {
            error_safe(err, "gnl error3");
            clear_points(points, i);
            return NULL;
        }
        points[i] = get_points_from_line(line);
        i++;
    }
    return (points);
}

int **get_faces(int faces_cnt, int fd, char **err) {
    int **faces;
    char *line;
    int i;
    
    i = 0;
    if ((faces = (int**)malloc(sizeof(int*) * faces_cnt)) == NULL)
        ft_error("Can't allocate memory");
    while (i < faces_cnt) {
        if (get_next_line(fd, &line) == 0) {
            error_safe(err, "gnl error3");
            clear_faces(faces, i);
            return NULL;
        }
        faces[i] = get_faces_from_line(line);
        i++;
    }
    return (faces);
    
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
        int first_point_position = faces[i][1];
        int second_point_position = faces[i][2];
        int third_point_position = faces[i][3];
        FLT3 tmp = {points[first_point_position][0], points[first_point_position][1], points[first_point_position][2]};
        i++;
    }
    
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

    
    
    
    
    
}




int common_check_off(int fd, char **err) {
    
    int last_line_count;
    int vertices_faces[2];
    char *line;
    
    if (check_format(fd, err))
        return (1);
    if (check_params(fd, vertices_faces, err))
        return (1);
    if (check_vertices(fd, vertices_faces, err))
        return (1);
    if (check_faces(fd, vertices_faces, err))
        return (1);
    last_line_count = get_next_line(fd, &line);
    if (last_line_count != 0) {
        error_safe(err, "last element not empty\n");
        return (1);
    }
    return (0);
}

int check_format(int fd, char **err) {
    char *c;
    int gn;
    int res;
    
    if ((gn = get_next_line(fd, &c)) == 0)
        return (error_safe(err, "gnl error1"));
    res = ft_strcmp(c, "OFF");
    if (res != 0) {
        return (error_safe(err, "wrong format - expected OFF"));
    }
    return (0);
}

int check_params(int fd, int *params, char **err) {
    char *c;
    int i;
    char **splits;
    
    i = 0;
    get_next_line(fd, &c);
    splits = ft_strsplit(c, 32);
    if (check_params_count(splits, 3, err))
        return (1);
    while (i < 3) {
        params[i] = ft_atoi(splits[i]);
        if (i != 2 && params[i] == 0) {
            error_safe(err, "params need be not zero");
            return (1);
        }
        i++;
    }
    return (0);
}

int check_params_count(char **splits, int count, char **err) {
    int i;
    
    i = 0;
    if (splits == NULL) {
        error_safe(err, "empty line from gnl");
        return (1);
    }
    while (splits[i] != NULL) {
        i++;
    }
    if (i != count) {
        error_safe(err, "wrong count params");
        return (1);
    }
    return (0);
}

int check_vertices(int fd, int *params, char **err) {
    int verticles;
    int i;
    char *line;
    
    verticles = params[0];
    i = 0;
    while (i < verticles) {
        get_next_line(fd, &line);
        if (check_element_count(line, 3, err))
            return (1);
        i++;
    }
    return (0);
}

int check_element_count(char *line, int count, char **err) {
    char **splits;
    
    splits = ft_strsplit(line, 32);
    if (check_params_count(splits, count, err))
        return (1);
    free_splits(splits, count);
    return (0);
}

void free_splits(char **splits, int count) {

    while (count != 0) {
        count--;
        free(splits[count]);
    }
    free(splits);
}


int check_faces(int fd, int *params, char **err) {
    int faces;
    int i;
    char *line;
    
    faces = params[1];
    i = 0;
    while (i < faces) {
        get_next_line(fd, &line);
        if (check_element_count(line, 4, err))
            return (1);
        if (*line != '3' && line[1] != ' ') {
            error_safe(err, "wrong count of points in faces");
            return (1);
        }
            
        i++;
    }
    return (0);
}
