/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndudnicz <ndudnicz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 17:42:41 by ndudnicz          #+#    #+#             */
/*   Updated: 2017/11/01 17:42:42 by ndudnicz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "config.h"
#include "packet.h"
#include "make_connection.h"
#include "user_input.h"
#include "error.h"
#include "options_handling.h"

/*
** Display a usefull usage message.
*/

int		usage(char const *bin)
{
	printf("Usage: %s [options] <ip> <port>\n", bin);
	return (1);
}

/*
** The beginning of everything.
*/

int		main(int ac, char **av)
{
	t_config	*config;

	if (ac < 3)
		return (usage(av[0]));
	else if (!(config = create_config(av[0])))
		return (1);
	else
	{
		if (get_options(config, &ac, av) > 0)
			return (1);
		else if (make_connection(config, av[1], av[2]) > 0)
			return (1);
		else if (user_input_loop(config, 0, NULL) > 0)
			return (1);
		else
			return (0);
	}
}
