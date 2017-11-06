/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndudnicz <ndudnicz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 17:44:57 by ndudnicz          #+#    #+#             */
/*   Updated: 2017/11/01 17:44:58 by ndudnicz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "libftasm.h"
#include "config.h"
#include "packet.h"
#include "switch_packet_type_server.h"
#include "error.h"
#include "options_handling.h"
#include "open_connection.h"
#include "waiting_loop.h"

/*
** Display a usefull usage message.
*/

int		usage(char const *bin)
{
	printf("Usage: %s [options] <port>\n\n", bin);
	printf("Options:\n\n");
	printf("\t-f <root_folder> : set a root folder\n");
	return (1);
}

/*
** The beginning of everything.
*/

int		main(int ac, char **av)
{
	t_config	*config;

	if (ac < 2)
		return (usage(av[0]));
	else if (!(config = create_config(av[0])))
		return (1);
	else
	{
		if (get_options(config, &ac, av) > 0)
			return (1);
		else if (open_cmd_connection(config, av[1]) > 0)
			return (1);
		else if (master_waiting_loop(config) > 0)
			return (1);
		else
			return (0);
	}
}
