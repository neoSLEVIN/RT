#include "ocl.h"

_Bool	ppm_error_safe(char **err, const char *text, DTO_PPM_IMG **dto)
{
	if (!(*err = ft_strdup(text)))
		ft_error("Can't allocate memory");
	if (dto && *dto)
		ft_memdel((void**)dto);
	return (FALSE);
}
