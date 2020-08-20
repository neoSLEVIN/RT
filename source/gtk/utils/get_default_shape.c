#include "gtk_module.h"

SHAPE	*get_default_shape(SHAPE *shape, DTO_SHAPE *dto)
{
	shape->tree_iter = NULL;
	shape->name = NULL;
	shape->next = NULL;
	shape->prev = NULL;
	shape->widgets = NULL;
	shape->texture_name = NULL;
	shape->normal_map_name = NULL;
	shape->dto = dto;
	return (shape);
}
