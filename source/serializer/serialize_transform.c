#include "serializer.h"

static cl_float	get_shape_rotation_angle(TRANSFORM *trans)
{
	cl_float	angle;
	FLT3		upguide;

	angle = v3_angle_to_xz(trans->rotation);
	upguide = v3_norm(v3_cross(trans->rotation, trans->direction));
	if (v3_angle_to_xz(upguide) < 0.0f)
		angle = ((angle < 0) ? -PI : PI) - angle;
	if (angle == 0.0f && upguide.y == 0.0f)
		angle = -atan2f(trans->rotation.z, -trans->rotation.x);
	return (angle);
}

void			s_transform_obj(t_serializer *s, TRANSFORM *transform,
								SHAPE_TYPE type)
{
	s_open_obj_with_name(s, "transform");
	s_name(s, "position");
	s_float3(s, transform->position);
	s_comma(s);
	s_name(s, "direction");
	s_float3(s, v3_norm(transform->direction));
	//TODO for cube/box triangle
	if (type == CAPPEDPLANE)
	{
		s_comma(s);
		s_name(s, "rotate angle");
		s_float(s, rad_to_deg(get_shape_rotation_angle(transform)));
	}
	s_close_obj(s);
}
