#include <stdlib.h>

#include "libftasm.h"
#include "libft.h"
#include "config.h"
#include "packet.h"
#include "error_child.h"
#include "error_master.h"
#include "error_message.h"

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

t_config	*create_config(char const*exec_name)
{
	t_config	*new;

	if (!(new = (t_config*)malloc(sizeof(t_config))))
	{
		ft_error_child(exec_name, "", MALLOC_FAIL);
		return (NULL);
	}
	ft_bzero((char*)new, sizeof(t_config));
	if (!(new->buf = (char*)malloc(MAX_PACKET_SIZE)))
	{
		ft_error_child(exec_name, "", MALLOC_FAIL);
		return (NULL);
	}
	return (new);
}

int			free_config(t_config *config)
{
	free(config->buf);
	free(config->current_path);
	free(config);
	return (0);
}
