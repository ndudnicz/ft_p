#include <stdio.h>
#include "libft.h"
#include "libftasm.h"
#include "establish_connection.h"
#include "user_input.h"

int		usage(char const *bin)
{
	printf("Usage: %s <ip> <port>\n", bin);
	return (1);
}

int		main(int ac, char **av)
{
	char *line;

	if (ac != 3)
		return (usage(av[0]));
	establish_connection(av[1], av[2]);
	loop();
	return (0);
}
