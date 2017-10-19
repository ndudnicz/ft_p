#include "libft.h"
#include <stdio.h>
#include "libftasm.h"

int		loop(void)
{
	char	*line;

	line = NULL;
	ft_putstr("client> ");
	while (gnl(0, &line) > 0)
	{
		puts(line);
		ft_putstr("client> ");
	}
	ft_putendl("Bye!");
	return (0);
}
