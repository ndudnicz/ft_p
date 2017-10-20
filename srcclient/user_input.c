#include "libft.h"
#include <stdio.h>
#include "libftasm.h"
#include "user_input.h"
#include "error_input.h"

static int	treat_input(t_treated_input *input, char const *line)
{
	char const	**array = (char const**)ft_strsplit(ft_strtrim(line), ' ');

	if (!array)
	{
		return (0);
	}
	else
	{
		for (int i = 0; array[i]; i++)
			printf("%s\n", array[i]);
	}
	return (1);
}

/*
** Loop and treat the input string while the user doesn't type 'quit' or press
** CTRL-D
*/

int		loop(void)
{
	char				*line;
	t_treated_input		input;

	line = NULL;
	ft_putstr("ftp> ");
	while (gnl(0, &line) > 0 && treat_input(&input, line))
	{
		//puts(line);
		ft_putstr("ftp> ");
	}
	ft_putendl("Bye!");
	return (0);
}
