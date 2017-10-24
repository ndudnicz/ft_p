#include <stdlib.h>

#include "libftasm.h"
#include "config.h"
#include "packet.h"

/*
** Create and return a copy of c.
*/

t_config	*configdup(t_config *c)
{
	t_config	*new;
	size_t		size;

	size = sizeof(t_config);
	if (!(new = (t_config*)malloc(size)))
		return (NULL);
	ft_memcpy(new, c, size);
	if (!(new->buf = (char*)malloc(MAX_PACKET_SIZE)))
		return (NULL);
	else if (!(new->current_path = ft_strdup(c->current_path)))
		return (NULL);
	else
		return (new);
}
