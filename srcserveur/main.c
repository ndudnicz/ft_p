#include <stdio.h>

int		usage(char const *bin)
{
	printf("Usage: %s <port>\n", bin);
	return (1);
}

int		main(int ac, char **av)
{
	if (ac != 2)
		return (usage(av[0]));
	return (0);
}
