#include "config.h"
#include "libftasm.h"
#include <stdlib.h>

/*
** Create and return a copy of c.
*/

t_config	*configcpy(t_config *c)
{
	t_config	*new;
	size_t		size;

	size = sizeof(t_config);
	if (!(new = (t_config*)malloc(size)))
		return (NULL);
	return (ft_memcpy(new, c, size));
}
