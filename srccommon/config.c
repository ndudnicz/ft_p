/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndudnicz <ndudnicz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 17:43:09 by ndudnicz          #+#    #+#             */
/*   Updated: 2017/11/01 17:43:10 by ndudnicz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libftasm.h"
#include "libft.h"
#include "config.h"
#include "packet.h"
#include "error.h"
#include "debug.h"

/*
** Create and return a copy of c.
*/
/*
t_config	*configdup(t_config *c)
{
	t_config	*new;
	size_t		size;

	size = sizeof(t_config);
	if (!(new = (t_config*)malloc(size)))
		return (NULL);
	ft_memcpy(new, c, size);
	new->options |= DUPED;
	if (!(new->buf = (char*)malloc(MAX_PACKET_SIZE)))
		return (NULL);
	// else if (!(new->current_path = ft_strdup(c->current_path)))
		// return (NULL);
	else if (!(new->ip_str = ft_strdup(c->ip_str)))
		return (NULL);
	else
		return (new);
}
*/
t_config	*create_config(char const*exec_name)
{
	t_config	*new;

	if (!(new = (t_config*)malloc(sizeof(t_config))))
	{
		ft_error_child(exec_name, "", MALLOC_FAIL);
		return (NULL);
	}
	ft_bzero((char*)new, sizeof(t_config));
	if (!(new->buf = (char*)malloc(MAX_PACKET_SIZE + 1)))
	{
		ft_error_child(exec_name, "", MALLOC_FAIL);
		return (NULL);
	}
	return (new);
}

int			free_config(t_config *config)
{
	my_free(40,config->buf);
	my_free(41,config->ip_str);
	my_free(42,config);
	return (0);
}
