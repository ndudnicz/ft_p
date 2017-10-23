#include <stdlib.h>
#include <stdio.h>

#include "libft.h"
#include "libftasm.h"
#include "config.h"
#include "user_input.h"
#include "error_child.h"
#include "packet.h"
#include "debug.h"//
#include "send_packet.h"
#include "receive_packet.h"
#include "switch_packet_type_client.h"
#include "error_master.h"//

static unsigned short get_type(char const *str)
{
	if (!ft_strcmp("ls", str) || !ft_strcmp("LS", str))
		return (ST_LS);
	else if (!ft_strcmp("cd", str) || !ft_strcmp("CD", str))
		return (ST_CD);
	else if (!ft_strcmp("get", str) || !ft_strcmp("GET", str))
		return (ST_GET);
	else if (!ft_strcmp("put", str) || !ft_strcmp("PUT", str))
		return (ST_PUT);
	else if (!ft_strcmp("pwd", str) || !ft_strcmp("PWD", str))
		return (ST_PWD);
	else if (!ft_strcmp("lls", str) || !ft_strcmp("LLS", str))
		return (ST_LLS);
	else if (!ft_strcmp("lcd", str) || !ft_strcmp("LCD", str))
		return (ST_LCD);
	else if (!ft_strcmp("lpwd", str) || !ft_strcmp("LPWD", str))
		return (ST_LPWD);
	else
	{
		ft_error_child("ERROR", "INPUT", "UNKNOWN COMMAND");
		return (0);
	}
}

static int	treat_input(t_input *input, char const *line)
{
	char const	**array = (char const**)ft_strsplit(ft_strtrim(line), ' ');

	if (!array)
	{
		return (0);
	}
	else
	{
		input->cmd = get_type(array[0]);
		input->arg = array[1] ? (char*)array[1] : ft_strdup("no arg");
		//for (int i = 0; array[i]; i++)
			//printf("%s\n", array[i]);
	}
	return (1);
}

// static int		send_message(t_config *config, char const *msg, char const *side)
// {
// 	t_packet		hello;
// 	size_t const	size = (HEADER_SIZE + ft_strlen(msg)) << 16 | T_DATA;
//
// 	forge_packet(&hello, size, msg, 1);
// 	unforge_packet(&hello);
// 	// print_packet(hello, 1);
// 	forge_packet(&hello, size, msg, 1);
// 	if (send_packet(config, &hello) > 0)
// 		return (ft_error(side, "send_message()", CANT_ESTABLISH_CONNECTION, 1));
// 	else
// 		return (0);
// }

/*
** Loop and treat the input string while the user doesn't type 'quit' or press
** CTRL-D
*/

int		user_input_loop(t_config *config)
{
	char		*line;
	t_packet	*packet;
	t_input		input;

	packet = (t_packet*)malloc(sizeof(t_packet));
	line = NULL;
	ft_putstr("ftp> ");
	while (gnl(0, &line) > 0)
	{
		treat_input(&input, line);
		print_input(&input);
		// send_message(config, line, "client");
		ft_bzero((char*)packet, packet->size);
		// receive_cmd_packet(config, packet);
		// if (switch_packet_type_client(config, packet) > 0)
			// return (1);
		ft_putstr("ftp> ");
	}
	ft_putendl("Bye!");
	return (0);
}
