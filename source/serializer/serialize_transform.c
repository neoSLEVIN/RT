#include "serializer.h"

void	s_transform_obj(t_serializer *s, TRANSFORM *transform, SHAPE_TYPE type)
{
	s_open_obj_with_name(s, "transform");
	s_name(s, "position");
	s_float3(s, transform->position);
	s_comma(s);
	s_name(s, "direction");
	s_float3(s, v3_norm(transform->direction));
	//TODO for cube/box
	if (type == NONE)
	{
		s_comma(s);
		s_name(s, "rotation");
		s_float3(s, transform->rotation);
	}
	s_close_obj(s);
}
