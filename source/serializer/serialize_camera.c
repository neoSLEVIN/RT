#include "serializer.h"

static cl_float	get_cam_rotation(DTO_CAM *cam)
{
	cl_float	angle;

	angle = v3_angle_to_xz(cam->right);
	if (v3_angle_to_xz(cam->upguide) < 0.0f)
		angle = ((angle < 0) ? -PI : PI) - angle;
	if (angle == 0.0f && cam->upguide.y == 0.0f)
		angle = -atan2f(cam->right.z, -cam->right.x);
	return (angle);
}

void		s_camera_obj(t_serializer *s, DTO_CAM *cam, cl_float fov)
{
	s_open_obj_with_name(s, "camera");
	s_name(s, "position");
	s_float3(s, cam->origin);
	s_comma(s);
	s_name(s, "direction");
	s_float3(s, v3_norm(cam->forward));
	s_comma(s);
	s_name(s, "rotation");
	s_float(s, rad_to_deg(get_cam_rotation(cam)));
	s_comma(s);
	s_name(s, "fov");
	s_float(s, fov);
	s_close_obj(s);
}
