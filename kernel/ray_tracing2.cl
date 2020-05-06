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
	int					uid;
	int					marker;
}						t_light;

typedef struct			s_transform
{
	float3				position;
	float3				direction;
	float3				rotation;
}						t_transform;

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
	t_transform			transform;
}						t_cam;

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

typedef struct			s_object
{
	t_shape_type		type;
	t_transform			transform;
	t_material			material;
	float				radius;
	int					uid;
	int					marker;
}						t_object;

__kernel void render_kernel(__global t_object *objects,
							int num_obj,
							__global t_light *lights,
							int num_light,
							t_cam cam,
							__global float3* output,
							__global unsigned int *seedsInput)
{
	const int work_item_id = get_global_id(0);
	if (cam.origin.x == 0)
		output[work_item_id] = (float3)(work_item_id % 256, work_item_id % 256, 0);
	else
		output[work_item_id] = (float3)(work_item_id % 256, 0, work_item_id % 256);
}
