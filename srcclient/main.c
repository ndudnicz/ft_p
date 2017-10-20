#include <stdio.h>
#include "libft.h"
#include "libftasm.h"
#include "establish_connection.h"
#include "user_input.h"
#include "config.h"
#include <stdlib.h>
#include "error_master.h"
#include "options_handling.h"

/*
** Display a usefull usage message.
*/

int		usage(char const *bin)
{
	printf("Usage: %s [options] <ip> <port>\n", bin);
	printf("Options:\n\t-z : toto\n\t-n : lol\n");
	return (1);
}

/*
** The beginning of everything.
*/

int		main(int ac, char **av)
{
	t_config	*config;

	if (ac < 3)
	{
		return (usage(av[0]));
	}
	else if (!(config = (t_config*)malloc(sizeof(t_config))))
	{
		return (ft_error(av[0], "", MALLOC_FAIL, 1));
	}
	else
	{
		if (get_options(config, &ac, av) > 0)
			return (1);
		establish_connection(av[1], av[2]);
		loop();
	}
	return (0);
}
