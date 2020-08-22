#ifndef SERIALIZER_H
# define SERIALIZER_H

# include "stdio.h"
# include "libft.h"
# include "scene.h"

typedef struct		s_serializer
{
	int				fd;
	int				indents;
}					t_serializer;

/*
** ============================== Base functions ===============================
*/
void				s_open_serializer(t_serializer *s, const char *filename);
void				s_close_serializer(t_serializer *s);
void				s_indent_inc(t_serializer *s);
void				s_indent_dec(t_serializer *s);
void				s_indent(t_serializer *s);
void				s_comma(t_serializer *s);
void				s_null(t_serializer *s);
void				s_bool(t_serializer *s, _Bool bool_value);
void				s_float(t_serializer *s, float num_value);
void				s_str(t_serializer *s, const char *str);
void				s_str_free(t_serializer *s, char *str);
void				s_str_in_quotes(t_serializer *s, const char *str);
void				s_str_in_quotes_free(t_serializer *s, char *str);
void				s_open_json_obj(t_serializer *s);
void				s_open_obj(t_serializer *s);
void				s_open_arr(t_serializer *s);
void				s_name(t_serializer *s, const char *name);
void				s_open_obj_with_name(t_serializer *s, const char *name);
void				s_open_arr_with_name(t_serializer *s, const char *name);
void				s_close_obj(t_serializer *s);
void				s_close_arr(t_serializer *s);
/*
** ============================== Scene functions ==============================
*/
char				*get_filter_type_name(FILTER filter);
char				*get_shape_type_name(SHAPE_TYPE type);
char				*get_light_type_name(LIGHT_TYPE type);
void				s_float3(t_serializer *s, FLT3 num_value);
void				s_json_obj(const char *scene_filename, SCENE *scene);
void				s_settings_obj(t_serializer *s, SCENE *scene);
void				s_scene_obj(t_serializer *s, SCENE *scene);
void				s_camera_obj(t_serializer *s, DTO_CAM *cam);
void				s_shapes_arr(t_serializer *s, SHAPE *shape,
								PPM_IMG *textures, PPM_IMG *normal_maps);
void				s_lights_arr(t_serializer *s, LIGHT *light);
void				s_ppm_img_arr(t_serializer *s, const char *name,
								PPM_IMG *ppm);
void				s_shape_ppm_img_obj(t_serializer *s, int id,
								const char *name, PPM_IMG *ppm);
void				s_transform_obj(t_serializer *s, TRANSFORM *transform);
void				s_material_obj(t_serializer *s, MATERIAL *material);
void				s_sections_obj(t_serializer *s, DTO_SHAPE *dto);

#endif
