#include "libft.h"
#include <stdio.h>
#include "libftasm.h"
#include "user_input.h"
#include "error_child.h"
#include "packet.h"
#include <stdlib.h>
#include "debug.h"//
#include "send_packet.h"
#include "receive_packet.h"

static int	treat_input(t_treated_input *input, char const *line)
{
	char const	**array = (char const**)ft_strsplit(ft_strtrim(line), ' ');

	if (!array)
	{
		return (0);
	}
	else
	{
		//for (int i = 0; array[i]; i++)
			//printf("%s\n", array[i]);
	}
	return (1);
}

/*
** Loop and treat the input string while the user doesn't type 'quit' or press
** CTRL-D
*/

int		user_input_loop(t_config *config)
{
	char				*line;
	t_treated_input		input;
	t_packet			*packet;

	packet = (t_packet*)malloc(sizeof(t_packet));
	line = NULL;
	ft_putstr("ftp> ");
	while (gnl(0, &line) > 0 && treat_input(&input, line))
	{
		forge_packet(packet, ((ft_strlen(line) + HEADER_SIZE) << 16 & (T_MASK_CMD | ST_LS)), line, ft_strlen(line));
		print_forged_packet(packet, 1);
		send_packet(config, packet);
		ft_bzero(packet->data, packet->size - HEADER_SIZE);
		receive_cmd_packet(config);
		ft_putstr("ftp> ");
	}
	ft_putendl("Bye!");
	return (0);
}
