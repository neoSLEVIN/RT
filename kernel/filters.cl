

void filter_sepia(float3 *color, float depth)
{
	float average;
	
	average = (color->x + color->y + color->z) / 3;
	
	color->x = average + depth * 2;
	color->y = average + depth;
	color->z = average;
}

void filter_negative(float3 *color)
{
	color->x  = 1.0f - color->x ;
	color->y = 1.0f - color->y;
	color->z = 1.0f - color->z;
}

void filter_noise(float3 *color, float noise)
{
	color->x += noise;
	color->y += noise;
	color->z += noise;
}

void filter_shades_of_gray(float3 *color)
{
	float average;
	
	average = (color->x + color->y + color->z) / 3;
	color->x = average;
	color->y = average;
	color->z = average;
}

void apply_filter(float3 *color, FILTER filter)
{
	float depth_sepia = 30.0f / 255.0f;
	float noise = -50.0f / 255.0f;
	
	if (filter == SEPIA)
		filter_sepia(color, depth_sepia);
	if (filter == NEGATIVE)
		filter_negative(color);
	if (filter == NOISE)
		filter_noise(color, noise);
	if (filter == SHADES_OF_GRAY)
		filter_shades_of_gray(color);
}
