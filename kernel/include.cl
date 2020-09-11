__constant float MY_EPSILON = 0.00003f;
__constant float MY_INFINITY = 1e20f;

typedef enum			e_light_type
{
						AMBIENT,
						POINT,
						DIRECTION,
						CNT_OF_TYPES_L
}						t_light_type;

typedef enum			e_filters
{
						NO_FILTER,
						SEPIA,
						NEGATIVE,
						NOISE,
						SHADES_OF_GRAY,
						BLUR,
						EMBOSS,
						SHARPEN
}						FILTER;

typedef struct			s_light
{
	t_light_type		type;
	float				intensity;
	float3				position;
	float3				direction;
}						t_light;

typedef struct			s_transform
{
	float3				position;
	float3				direction;
	float3				rotation;
	float				angle;
	float3				dots[3];
}						t_transform;

/*Ray cam*/
typedef struct			s_cam
{
	int					screen_w;
	int					screen_h;
	int2				max_screen;
	int2				diff_screen;
	float				viewport_h;
	float				viewport_w;
	float3				origin;
	float3				target;
	float3				forward;
	float3				up;
	float3				right;
	float3				upguide;
}						CAMERA;


/*Object's elements*/
typedef enum			e_shape_type
{
						NONE,
						PLANE,
						SPHERE,
						CONE,
						CAPPEDCONE,
						CYLINDER,
						CAPSULE,
						CAPPEDCYLINDER,
						CIRCLE,
						CAPPEDPLANE,
						BOX,
						TRIANGLE,
						OFF
}						t_shape_type;

typedef struct			s_material
{
	float3				color;
	float				specular;
	float3				emission;
	float				reflective;
	float				transparency;
	float				degree_of_refraction;
}						t_material;

typedef struct			s_texture
{
	int					id;
	float3				direction;
	float				rotation;
}						t_texture;

typedef struct			s_section
{
	bool				on;
	t_shape_type		type;
	float3				position;
	float3				direction;
	float				radius;
}						t_section;

typedef struct			s_object
{
	t_shape_type		type;
	t_transform			transform;
	t_material			material;
	t_texture			texture;
	t_texture			normal_map;
	t_section			section[6];
	int					working_sections;
	bool				is_complex_section;
	float3				params;
	bool				marker;
}						t_object;


typedef struct			s_dto_ppm_img
{
	uchar 				data[1440*1440*3];
	int 				width;
	int 				height;
	int 				max_color;
	int					start_image;
}						t_ppm_image;

/*тут будем хранить прозрачный объект. Используется только в kernel*/
typedef struct			s_transparent_obj
{
	float				t;
	int					hit_id;
}						t_transparent_obj;

typedef struct			s_ray
{
	float3				origin;
	float3				dir;
	float				t;
	float3				hitPoint;
	float3				hitNormal;
	int					hit_id;
	int					index;
	t_shape_type		hit_type;
}						t_ray;


typedef struct				s_scene
{
	__global t_object  		*objects;
	int 					num_obj;
	__global t_light 		*lights;
	int 					num_light;
	CAMERA 					cam;
	uint					seed;
	int2 					cursor;
	__global t_ppm_image	*textures;
	__global t_ppm_image	*normal_maps;
	int						mirror;
	__global float3			*points;
	__global int3			*faces;
	__global float3			*colors;
	int						point_cnt;
	int						faces_cnt;
}							t_scene;





void init_scene(t_scene *scene,
				__global t_object *objects,
				int num_obj,
				__global t_light *lights,
				int num_light,
				CAMERA cam,
				uint seed,
				__global t_ppm_image *textures,
				__global t_ppm_image *normal_maps,
				int mirror,
				__global float3 *points,
				__global int3 *faces,
				__global float3 *colors,
				int point_cnt,
				int faces_cnt);

float3 compute_color(t_scene *scene, t_ray *ray);

void	reinit_off_obj(t_object *obj, t_scene *scene, t_ray *ray);

float cappedplane_intersect(t_ray *ray, t_object *plane);
/*Mapping*/
float2 sphere_map(t_object *obj, t_ray *ray);
float2 plane_map(t_object *obj, t_ray *ray, int size);
float2 box_map(t_object *obj, t_ray *ray, int size);
float2 cylindrical_map(t_object *obj, t_ray *ray, int size);
float2 capped_cylindrical_map(t_object *obj, t_ray *ray, int size);
float2 capped_cone_map(t_object *obj, t_ray *ray, int size);
float2 translate_plane_coord(float3 plane_norm, t_ray *ray);
void 	set_uv_basis(float3 normal, float3 *u_basis, float3 *v_basis);
/*main*/
float3 image_texture(float2 uv, __global t_ppm_image *texture, int id);
float2 get_uv(t_object *obj, t_ray *ray, int splits);
/*patterns*/
float3 uv_patter_checker(int checkerW, int checkerH, float2 uv);
float3 uv_patter_lines(float2 uv);
float3 uv_patter_circle(float2 uv, t_object *obj);
float3 plane_checker(t_object *obj, t_ray *ray);
float3 plane_lines_cross(t_object *obj, t_ray *ray);
float3 uv_patter_plane_lines_cross(float2 uv);
float3 typical_noise(t_object *obj, float2 uv, int size);
float3 wood(t_object *obj, float2 uv, int size);
float noise(float x, float y);
float surflet( float x, float y, float grad_x, float grad_y );
float f( float t );
float2 translate_plane_coord_with_static(float3 plane_norm, t_ray *ray, float3 plane_pos);

float3 	sphere_normal(float3 hitpoint, float3 position);
float3 	plane_normal(float3 planeDir, float3 rayDir);
float3 	cyl_normal(t_object *hit_obj, t_ray *ray);
float3 	capsule_normal(t_object *hit_obj, t_ray *ray);
float3 	cone_normal(t_object *hit_obj, t_ray *ray);
float3 	capped_cone_normal(t_object *hit_obj, t_ray *ray);
float3	capped_cylinder_normal(t_object *hit_obj, t_ray *ray);
float3	triangle_normal(t_object *hit_obj);
float3	get_normal(t_object *hit_obj, t_ray *ray, t_scene *scene);

float	compute_sections(t_ray *ray, t_section *sections, int is_complex, float t1, float t2);

float	sphere_intersect(t_ray *ray, t_object *sphere);
float	plane_intersect(t_ray *ray, t_object *plane);
float	cylinder_intersect(t_ray *ray, t_object *cylinder);
float	cone_intersect(t_ray *ray, t_object *cone);
float	capped_cylinder_intersect(t_ray *ray, t_object *capped_cylinder);
float	triangle_intersect(t_ray *ray, t_object *triangle);
float	off_intersect(t_ray *ray, t_object *off, t_scene *scene, int *part_index);
bool 	is_intersect(t_ray *ray, t_scene *scene, t_transparent_obj *skip_transparent);
float 	minT(float a, float b);
float	module(float a);

float 	get_light_intensity(t_ray *ray, t_scene *scene);
float 	get_point_light(t_light *light, t_ray *ray, t_scene *scene);
float 	get_dir_light(t_light *light, t_ray *ray, t_scene *scene);
bool 	is_in_shadow_point(t_light *light, t_ray *ray, t_scene *scene, float *transparent_coef);
bool 	is_in_shadow_directional(t_light *light, t_ray *ray, t_scene *scene, float *transparent_coef);

float	diffuse_light(t_light *light, t_ray *ray, float specular);
float	compute_specular(float3 normal_to_intersect, float3 light_vector, float3 rayDir, float object_specular);

float 	get_random(uint *state);

float3 	go_reflect(t_ray ray, t_scene *scene);
float3 	continue_reflect_ray(t_ray *ray, t_scene *scene);
float3 	reflect_ray(t_ray ray, t_scene *scene);
float3 	reflect(float3 rayDir, float3 targetNormal);

float3 	go_refract(t_ray ray, t_scene *scene);
float3	continue_refract_ray(t_ray *ray, t_scene *scene);
float3	refract(t_ray *ray, float degree);

float3	get_obj_color(t_object *obj, t_ray *ray, t_scene *scene);
char	convertColorFromFloat(float f);

float3	send_ray(t_ray *ray, t_scene *scene);
void	init_ray(t_ray *ray, CAMERA *cam, int work_id, float rand);

void	filter_sepia(float3 *color, float depth);
void	filter_negative(float3 *color);
void	filter_noise(float3 *color, float noise);
void	filter_shades_of_gray(float3 *color);
void	apply_filter(float3 *color, FILTER filter, float3 filter_params);

float3 refract1(t_ray *ray);
float3 refract_v1(t_ray *ray);
uint xorshift32(uint *state);
void set_t(t_ray *ray, t_object *selected_obj, t_transparent_obj *skiped, float t, int i, int part_index);
void make_ray_empty(t_ray *ray);
float box_intersect(t_ray *ray, t_object *cube, int *index);
float capped_cone_intersect(t_ray *ray, t_object *capped_cone, int *index);
float capsule_intersect(t_ray *ray, t_object *capsule, int *index);
float circle_intersect(t_ray *ray, t_object *circle);
float minTwithIndexes(float a, float b, int index_a, int index_b, int *result_index);
float semi_cone_intersect(t_ray *ray, t_object *cone, float len, float shift);
float semi_cylinder_intersect(t_ray *ray, t_object *cylinder, float len);
float semi_sphere_intersect(t_ray *ray, t_object *sphere, float3 cut_normal);
float	compute_simple_sections(t_ray *ray, t_section *sections, float3 *t_point, float2 new_t);
float	compute_complex_sections(t_ray *ray, t_section *sections, float3 *t_point, float2 old_t);
float2	cut_by_plane_section(float3 *t_point,
							float3 section_pos, float3 section_dir,
							float2 new_t);
float2	cut_by_sphere_section(t_ray *ray,
							float3 section_pos, float section_radius,
							float2 new_t);
float3 apply_normal_map(t_object *hit_obj, t_ray *ray, float3 normal, t_scene *scene, int id);
int is_outside_capped_cylinder(t_ray *ray, t_object *capped_cylinder, float value);
float3 box_normal(t_object *hit_obj, t_ray *ray);


