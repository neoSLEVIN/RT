#include "jc_parser.h"

_Bool	jc_get_bool_or_default(const JC_FIELD parent, const char *child_name,
							_Bool default_value)
{
	JC_FIELD	bool_field;

	bool_field = jc_get_field(parent, child_name, (JC_BOOL | JC_NULL));
	if (jc_is_null(bool_field))
		return (default_value);
	return ((bool_field.obj->value.start[0] == 't') ? TRUE : FALSE);
}

_Bool	jc_get_bool(const JC_FIELD parent, const char *child_name)
{
	JC_FIELD	bool_field;

	bool_field = jc_get_field(parent, child_name, JC_BOOL);
	return ((bool_field.obj->value.start[0] == 't') ? TRUE : FALSE);
}
