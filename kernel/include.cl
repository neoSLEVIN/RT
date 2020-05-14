__constant float EPSILON = 0.00003f;

typedef enum			e_light_type
{
						AMBIENT,
						POINT,
						DIRECTION,
						CNT_OF_TYPES_L
}						t_light_type;

typedef struct			s_light
{
	t_light_type		type;
	float				intensity;
	float3				position;
	float3				target;
	int					marker;
}						t_light;

typedef struct			s_transform
{
	float3				position;
	float3				direction;
	float3				rotation;
}						t_transform;

/*Ray cam*/
typedef struct			s_cam
{
	int					screen_w;
	int					screen_h;
	float				viewport_h;
	float				viewport_w;
	float3				origin;
	float3				target;
	float3				forward;
	float3				up;
	float3				right;
	float3				upguide;
}						CAMERA;


typedef struct			s_ray
{
	float3				origin;
	float3				dir;
	float				t;
	float3				hitPoint;
	float3				hitNormal;
	int					hit_id;
}						t_ray;

/*Object's elements*/
typedef enum			e_shape_type
{
						PLANE,
						SPHERE,
						CONE,
						CYLINDER,
						CNT_OF_TYPES
}						t_shape_type;

typedef struct			s_material
{
	float3				color;
	int					specular;
	float3				emission;
	float				reflective;
	float				transparency;
}						t_material;

/*Nazarov*/
typedef struct			s_section
{
	bool				on_x;
	bool				on_y;
	bool				on_z;
	t_transform			x;
	t_transform			y;
	t_transform			z;
	t_transform			xyz;
	float3				color;
}						t_section;


typedef struct			s_object
{
	t_shape_type		type;
	t_transform			transform;
	t_material			material;
	float				radius;
	int					marker;
	/*Nazarov*/
	t_section			section;
}						t_object;



float3 	sphere_normal(float3 hitpoint, float3 position, float3 rayDir);
float3 	plane_normal(float3 planeDir, float3 rayDir);
float3 	cyl_normal(t_object *hit_obj, t_ray *ray);
float3 	cone_normal(t_object *hit_obj, t_ray *ray);
float3	get_normal(t_object *hit_obj, t_ray *ray);

float	sphere_intersect(t_ray *ray, t_object *sphere);
float	plane_intersect(t_ray *ray, t_object *plane);
float	cylinder_intersect(t_ray *ray, t_object *cylinder);
float	cone_intersect(t_ray *ray, t_object *cone);
bool 	is_intersect(t_ray *ray, __global t_object *obj, int num_obj, int* hit_id, float* distance);
float 	minT(float a, float b);

float 	get_light_intensity(t_ray *ray, __global t_object *obj, int num_obj, __global t_light *lights, int num_light);
bool 	is_in_shadow(t_light *light, t_ray *ray, __global t_object *obj, int num_obj);
float	diffuse_light(t_light *light, t_ray *ray, int specular);
float	compute_specular(float3 normal_to_intersect, float3 light_vector, float3 rayDir, int object_specular);

float 	get_random(uint *state);

float3 	go_reflect(t_ray ray, __global t_object *objects, int num_obj, __global t_light *lights, int num_light);
float3 	continue_reflect_ray(t_ray *ray, __global t_object *objects, int num_obj, __global t_light *lights, int num_light);
float3 	reflect_ray(t_ray ray, __global t_object *objects, int num_obj, __global t_light *lights, int num_light);
float3 	reflect(float3 rayDir, float3 targetNormal);

float3 	go_refract(t_ray ray, __global t_object *objects, int num_obj, __global t_light *lights, int num_light);
float3	continue_refract_ray(t_ray *ray, __global t_object *objects, int num_obj, __global t_light *lights, int num_light);
float3 	refract(t_ray *ray);

float3 	get_obj_color(t_object *obj, t_ray *ray);
char	convertColorFromFloat(float f);

float3 	send_ray(t_ray *ray, __global t_object *obj, int num_obj, __global t_light *lights, int num_light);
void 	init_ray(t_ray *ray, CAMERA *cam, int work_id, float rand);
