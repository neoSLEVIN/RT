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
	int					uid;
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
}						t_cam;


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

typedef struct			s_object
{
	t_shape_type		type;
	t_transform			transform;
	t_material			material;
	float				radius;
	int					uid;
	int					marker;
}						t_object;


void 		init_ray(t_ray *ray, t_cam *cam, int work_id, float rand);
float		sphere_intersect(t_ray *ray, t_object *sphere);
float 		get_light_intensity(t_ray *ray, __global t_object *obj, int num_obj, __global t_light *lights, int num_light);



/*Normals*/
float3 sphere_normal(float3 hitpoint, float3 position, float3 rayDir) {
	float3 normal;
	normal = normalize(hitpoint - position);
	/*
	return dot(rayDir, normal) < 0.0f ? normal : normal * (-1.0f);
	*/
	return normal;
}

float3 plane_normal(float3 planeDir, float3 rayDir) {
	float3 normal;
	float d;
	normal = planeDir;
	d = dot(rayDir, normal);
	if (d > 0)
		normal = normal * (-1.0f);
	return normal;
}

float3 cyl_normal(t_object *hit_obj, t_ray *ray) {
	float	m;
	float3	x;
	float3	tmp[3];
	float3	normal;

	x = ray->origin - hit_obj->transform.position;
	m = dot(ray->dir, hit_obj->transform.direction) * ray->t + dot(x, hit_obj->transform.direction);
	tmp[0] = ray->hitPoint - hit_obj->transform.position;
	tmp[1] = hit_obj->transform.direction * m;
	tmp[2] = tmp[0] - tmp[1];
	normal = normalize(tmp[2]);
	return normal;
}

float3 cone_normal(t_object *hit_obj, t_ray *ray) {
	float	k;
	float	m;
	float3	tmp[8];
	float3	normal;

	k = tan(hit_obj->radius);
	tmp[0] = ray->origin - hit_obj->transform.position;
	m = dot(ray->dir, hit_obj->transform.direction) * ray->t + dot(tmp[0], hit_obj->transform.direction);
	tmp[1] = ray->hitPoint - hit_obj->transform.position;
	tmp[2] = hit_obj->transform.direction * m;
	tmp[3] = tmp[1] - tmp[2];
	tmp[4] = hit_obj->transform.direction * m;
	tmp[5] = tmp[4] * k;
	tmp[6] = tmp[5] * k;
	tmp[7] = tmp[3] - tmp[6];
	normal = normalize(tmp[7]);
	return normal;
}

float3 get_normal(t_object *hit_obj, t_ray *ray) {
	float3 normal = 0;

	switch (hit_obj->type)
	{
		case SPHERE:
			normal = sphere_normal(ray->hitPoint, hit_obj->transform.position, ray->dir);
			break;
		case PLANE:
			normal = plane_normal(hit_obj->transform.direction, ray->dir);
			break;
		case CYLINDER:
			normal = cyl_normal(hit_obj, ray);
			break;
		case CONE:
			normal = cone_normal(hit_obj, ray);
			break;
	}
	return normal;
}


/*Intersection*/

float		sphere_intersect(t_ray *ray, t_object *sphere)
{
	float3		new_origin;
	float		coef[3];
	float		discriminant;
	float		t[2];

	new_origin = ray->origin - sphere->transform.position;
	coef[0] = dot(ray->dir, ray->dir);
	coef[1] = 2.0 * dot(ray->dir, new_origin);
	coef[2] = dot(new_origin, new_origin) - sphere->radius * sphere->radius;
	discriminant = coef[1] * coef[1] - 4.0 * coef[0] * coef[2];
	if (discriminant < 0.0) {
		return (0);
	}
	t[0] = (-coef[1] - sqrt(discriminant)) / (2.0 * coef[0]);
	t[1] = (-coef[1] + sqrt(discriminant)) / (2.0 * coef[0]);
	return t[0] > 0 ? t[0] : t[1];
}

float	plane_intersect(t_ray *ray, t_object *plane)
{
	float3	temp;
	float	d_dot_n;
	float	t;

	if ((d_dot_n = dot(ray->dir, plane->transform.direction)) == 0.0)
		return 0;
	temp = plane->transform.position - ray->origin;
	t = dot(temp, plane->transform.direction) / d_dot_n;
	return t;
}

float		cylinder_intersect(t_ray *ray, t_object *cylinder)
{
	float		abcd[4];
	float		t[2];
	float3		x;

	x = ray->origin - cylinder->transform.position;
	abcd[0] = dot(ray->dir, ray->dir) - pow(dot(ray->dir, cylinder->transform.direction), 2);
	abcd[1] = 2 * (dot(ray->dir, x) - (dot(ray->dir, cylinder->transform.direction) * dot(x, cylinder->transform.direction)));
	abcd[2] = dot(x, x) - pow(dot(x, cylinder->transform.direction), 2) - cylinder->radius * cylinder->radius;
	abcd[3] = pow(abcd[1], 2) - 4 * abcd[0] * abcd[2];
	if (abcd[3] < 0)
		return 0;
	t[0] = (-abcd[1] + sqrt(abcd[3])) / (2 * abcd[0]);
	t[1] = (-abcd[1] - sqrt(abcd[3])) / (2 * abcd[0]);
	return t[1] > 0 ? t[1] : t[0];
}

float	cone_intersect(t_ray *ray, t_object *cone)
{
	float		abc[3];
	float		t[2];
	float3		x;
	float		k_and_discr[2];

	x = ray->origin - cone->transform.position;
	k_and_discr[0] = 1 + tan(cone->radius) * tan(cone->radius);
	abc[0] = dot(ray->dir, ray->dir) - k_and_discr[0] * pow(dot(ray->dir, cone->transform.direction), 2);
	abc[1] = 2 * (dot(ray->dir, x) - k_and_discr[0] * dot(ray->dir, cone->transform.direction) * dot(x, cone->transform.direction));
	abc[2] = dot(x,x) - k_and_discr[0] * pow(dot(x, cone->transform.direction), 2);
	k_and_discr[1] = pow(abc[1], 2) - 4 * abc[0] * abc[2];
	if (k_and_discr[1] < 0)
		return (0);
	t[0] = (-abc[1] + sqrt(k_and_discr[1])) / (2 * abc[0]);
	t[1] = (-abc[1] - sqrt(k_and_discr[1])) / (2 * abc[0]);
	return t[1] > 0 ? t[1] : t[0];
}



bool is_intersect(t_ray *ray, __global t_object *obj, int num_obj, int* hit_id, float* distance)
{
	float inf = 1e20f;
	*distance = inf;

	int i = 0;
	float t = 0;
	ray->hit_id = -1;
	*hit_id = -1;
	while (i < num_obj)
	{
		t_object a1 = obj[i];
		if (obj[i].type == SPHERE)
			t = sphere_intersect(ray, &a1);
		else if (obj[i].type == PLANE)
			t = plane_intersect(ray, &a1);
		else if (obj[i].type == CYLINDER)
			t = cylinder_intersect(ray, &a1);
		else if (obj[i].type == CONE)
			t = cone_intersect(ray, &a1);
		if (t > EPSILON && t < *distance) {
			*distance = t;
			*hit_id = i;
		}

		i++;
	}
	return *distance < inf;
}



float3 send_ray(t_ray *ray, __global t_object *obj, int num_obj, __global t_light *lights, int num_light) {

	float t;
	int hit_id;
	float3 backColor = 0;
	float intensity;
	float3 resColor = 0;

	if (!is_intersect(ray, obj, num_obj, &hit_id, &t))
		return backColor;
	t_object hit_obj = obj[hit_id];
	ray->t = t;
	ray->hitPoint = ray->origin + t * ray->dir;
	ray->hitNormal = get_normal(&hit_obj, ray);
	ray->hit_id = hit_id;
	intensity = get_light_intensity(ray, obj, num_obj, lights, num_light);
	resColor = obj[hit_id].material.color * intensity;
	return resColor;
}


void init_ray(t_ray *ray, t_cam *cam, int work_id, float rand)
{

	ray->origin = cam->origin;
	float x = work_id % cam->screen_w;
	float y = work_id / cam->screen_w;
	float2 coord = (float2)(x + rand, y + rand );

	float2 viewport_coordinate;
	viewport_coordinate.x = ((2.0 * coord.x) / cam->screen_w) - 1;
	viewport_coordinate.y = ((-2.0 * coord.y) / cam->screen_h) + 1;

	float pixel_half = cam->viewport_w / cam->screen_w;
	ray->dir = cam->right * (viewport_coordinate.x * cam->viewport_w - pixel_half);
	ray->dir += cam->up * (viewport_coordinate.y * cam->viewport_h - pixel_half);
	ray->dir += cam->forward;
	ray->dir = normalize(ray->dir);
	ray->hit_id = -1;
}


char convertColorFromFloat(float f) {
	return floor(f >= 1.0 ? 255 : f * 256.0);
}


float	compute_specular(float3 normal_to_intersect, float3 light_vector, float3 rayDir, int object_specular)
{
	float n = 0;
	float3 R = 2 * normal_to_intersect * dot(normal_to_intersect, light_vector) - light_vector;
	float r_dot_v = dot(R, rayDir);
	if (r_dot_v > 0) {
		float tmp = length(R) * length(rayDir);
		n = pow( r_dot_v / tmp, object_specular);
	}
	return n;
}

float	diffuse_light(t_light *light, t_ray *ray, int specular) {
	float res;
	float angle;
	float3 light_vect;

	res = 0;
	light_vect = light->position - ray->hitPoint;
	angle = dot(ray->hitNormal, light_vect);

	if (angle > 0)
	{
		float tmp1 = light->intensity * angle;
		float tmp2 = length(ray->hitNormal) * length(light_vect);
		res += tmp1 / tmp2;
	}
	if (specular > 0)
	{
		float3 dir = normalize(ray->dir) * (-1.0f);
		float3 nor = ray->hitNormal;
		float b = compute_specular(nor, light_vect, dir, specular);
		res = res + (light->intensity * b);
	}
	return res;
}


bool is_in_shadow(t_light *light, t_ray *ray, __global t_object *obj, int num_obj) {
	float dist;
	float t;
	int hit_id;

	t_ray light_ray;
	dist = length(light->position - ray->hitPoint);
	light_ray.origin = light->position;
	light_ray.dir = normalize(ray->hitPoint - light->position);
	is_intersect(&light_ray, obj, num_obj, &hit_id, &t);
	if (t < dist - 0.01)
		return (1);
	return (0);
}


float get_light_intensity(t_ray *ray, __global t_object *obj, int num_obj, __global t_light *lights, int num_light) {
	float totalLight = 0;
	int i = 0;
	while (i < num_light) {
		if (lights[i].type == AMBIENT) {
			totalLight += lights[i].intensity;
		} else if (lights[i].type == POINT) {
			t_light light = lights[i];
			if (!is_in_shadow(&light, ray, obj, num_obj)) {
				int specular = obj[ray->hit_id].material.specular;
				totalLight += diffuse_light(&light, ray, specular);
			}

		}
		i++;
	}
	return totalLight;
}


uint xorshift32(uint *state)
{
	uint x = *state;
	x ^= x << 13;
	x ^= x >> 17;
	x ^= x << 5;
	return *state = x;
}

/*получаем в промежутке [0;1]*/
float get_random(uint *state)
{
	float res;
	uint rnd = xorshift32(state);
	res = (float)rnd / 4294967295;
	return res;
}

float3 reflect(float3 rayDir, float3 targetNormal) {
	float3 tmp = 2.0f * dot(rayDir, targetNormal) * targetNormal;
	return rayDir - tmp;
}


float3 refract(t_ray *ray) {
	/*cтепень преломления - воздух - 1 стекло - 1.5*/
	float ior = 1.0f;
	float eta;
	float3 hitNormal = ray->hitNormal;
	bool inside = dot(ray->dir, hitNormal) > 0;
	if (inside) {
		hitNormal = -hitNormal;
		eta = ior;
	} else {
		eta = 1.0f / ior;
	}
	float cosi = dot(-hitNormal, ray->dir);
	float k = 1 - eta * eta * (1.0f - cosi * cosi);

	float3 refDir = ray->dir * eta + hitNormal * (eta * cosi - sqrt(k));
	refDir = normalize(refDir);
	return refDir;
}

/*Меняет внутри луч*/
float3 continue_reflect_ray(t_ray *ray, __global t_object *objects, int num_obj, __global t_light *lights, int num_light) {
	ray->dir = reflect(ray->dir, ray->hitNormal);
	ray->origin = ray->hitPoint + (ray->hitNormal * 0.01f);
	return send_ray(ray, objects, num_obj, lights, num_light);
}

float3 reflect_ray(t_ray ray, __global t_object *objects, int num_obj, __global t_light *lights, int num_light) {
	ray.dir = reflect(ray.dir, ray.hitNormal);
	ray.origin = ray.hitPoint + (ray.hitNormal * 0.01f);
	return send_ray(&ray, objects, num_obj, lights, num_light);
}

float3 continue_refract_ray(t_ray *ray, __global t_object *objects, int num_obj, __global t_light *lights, int num_light) {
	
	int maxBounds = 3;
	int oldHit_id = ray->hit_id;
	
	while (oldHit_id == ray->hit_id && maxBounds != 0) {
		ray->dir = refract(ray);
		ray->origin = ray->hitPoint + ray->dir * 0.1f;

		if (!is_intersect(ray, objects, num_obj, &(ray->hit_id), &(ray->t))) {
			break;
		}
		
		t_object obj = objects[ray->hit_id];
		ray->hitPoint = ray->origin + ray->t * ray->dir;
		ray->hitNormal = get_normal(&obj, ray);
		maxBounds--;
	}
	
	float3 trans_color = 0;
	if (ray->hit_id > 0) {
		trans_color = objects[ray->hit_id].material.color * get_light_intensity(ray, objects, num_obj, lights, num_light);
	}
	return trans_color;
}

/**/
float3 go_reflect(t_ray ray, __global t_object *objects, int num_obj, __global t_light *lights, int num_light) {
	
	float3 finalColor = 0;
	
	/*цвет первого отраженного объекта*/
	finalColor = continue_reflect_ray(&ray, objects, num_obj, lights, num_light);
	
	/*простой объект*/
	if (objects[ray.hit_id].material.transparency == 0 && objects[ray.hit_id].material.reflective == 0) {
		return finalColor;
	}
	 
	/*объект отражает*/
	float ref = objects[ray.hit_id].material.reflective;
	if (ref > 0) {
		finalColor = finalColor * (1.0f - ref) + reflect_ray(ray, objects, num_obj, lights, num_light) * ref;
	}
	 
	/*объект обладает прозрачностью*/
	float trans = objects[ray.hit_id].material.transparency;
	if (trans > 0) {
		finalColor = finalColor * (1.0f - trans) + continue_refract_ray(&ray, objects, num_obj, lights, num_light) * trans;
	}
	
	return finalColor;
}

float3 go_refract(t_ray ray, __global t_object *objects, int num_obj, __global t_light *lights, int num_light) {
	
	float3 finalColor = 0;
	
	
	finalColor = continue_refract_ray(&ray, objects, num_obj, lights, num_light);
	
	if (objects[ray.hit_id].material.transparency == 0 && objects[ray.hit_id].material.reflective == 0) {
		return finalColor;
	}
	
	float ref = objects[ray.hit_id].material.reflective;
	if (ref > 0) {
		finalColor = finalColor * (1.0f - ref) + go_reflect(ray, objects, num_obj, lights, num_light) * ref;
	}
	
	/*объект обладает прозрачностью*/
	float trans = objects[ray.hit_id].material.transparency;
	if (trans > 0) {
		finalColor = finalColor * (1.0f - trans) + continue_refract_ray(&ray, objects, num_obj, lights, num_light) * trans;
	}
	
	return finalColor;
}


__kernel void render_kernel(__global t_object *objects,
							int num_obj,
							__global t_light *lights,
							int num_light,
							t_cam cam,
							__global char4* output,
							__global unsigned int *seedsInput)
{
	float3 finalColor = 0;
	t_ray ray;
	const int work_item_id = get_global_id(0);
	/*Набор случайных чисел*/
	uint seed = seedsInput[work_item_id];


	/*Сглаживание*/
	for (int i = 0; i < 6; i++) {
		float rnd = (2 * get_random(&seed) - 1) / 2;
		init_ray(&ray, &cam, work_item_id, rnd);

		float3 finalColor1 = send_ray(&ray, objects, num_obj, lights, num_light);


		if (ray.hit_id >= 0) {
			float ref = objects[ray.hit_id].material.reflective;
			float trans = objects[ray.hit_id].material.transparency;
			
			if (ref == 0 && trans == 0) {
				finalColor += finalColor1;
			} else {
				
				if (ref > 0) {
					
					finalColor += finalColor1 * (1.0f - ref) + go_reflect(ray, objects, num_obj, lights, num_light) * ref;
					
				}
				
				if (trans > 0) {
					
					finalColor += finalColor1 * (1.0f - trans) + go_refract(ray, objects, num_obj, lights, num_light) * trans;

				}
				
			}
		}

	}
	finalColor /= 6.0f;


	char red = convertColorFromFloat(finalColor.x);
	char green = convertColorFromFloat(finalColor.y);
	char blue = convertColorFromFloat(finalColor.z);
	char alfa = 255;

	output[work_item_id] = (char4)(red, green, blue, alfa);

	seedsInput[work_item_id] = seed;
}
