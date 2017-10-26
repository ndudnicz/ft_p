#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <arpa/inet.h>

#include "packet.h"
#include "libftasm.h"
#include "packet.h"
#include "config.h"
#include "switch_packet_type_server.h"
#include "error_master.h"
#include "options_handling.h"
#include "open_connection.h"
#include "debug.h"//
#include "waiting_loop.h"

/*
** Display a usefull usage message.
*/

int		usage(char const *bin)
{
	printf("Usage: %s [options] <port>\n\n", bin);
	printf("Options:\n\n");
	printf("\t-f <root_folder> : set a root folder\n");
	printf("\t-b <ip>          : bind the connection on <ip>\n");
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
			return (free_config(config));
	}
}
