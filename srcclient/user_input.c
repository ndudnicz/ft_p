#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>//
#include <sys/time.h>//
#include <sys/resource.h>//
#include <sys/wait.h>//

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
#include "exec_cmd_local.h"

static unsigned short get_type(char const *str)
{
	if (!ft_strcmp_nocase("ls", str))
		return (ST_LS);
	else if (!ft_strcmp_nocase("cd", str))
		return (ST_CD);
	else if (!ft_strcmp_nocase("get", str))
		return (ST_GET);
	else if (!ft_strcmp_nocase("put", str))
		return (ST_PUT);
	else if (!ft_strcmp_nocase("pwd", str))
		return (ST_PWD);
	else if (!ft_strcmp_nocase("lls", str))
		return (ST_LLS);
	else if (!ft_strcmp_nocase("lcd", str))
		return (ST_LCD);
	else if (!ft_strcmp_nocase("lpwd", str))
		return (ST_LPWD);
	else
	{
		ft_error_child("ERROR", "INPUT", "UNKNOWN COMMAND");
		return (0);
	}
}

static int	treat_input(t_input *input, char *line)
{
	char const	*s = ft_strtrim(line);
	char const	**array = (char const**)ft_strsplit(s, ' ');
	int			i;

	i = 0;
	free(line);
	// input->cmd = 0;
	// input->arg = NULL;
	if (!array)
		return (0);
	else
	{
		input->cmd = get_type(array[0]);
		input->arg = array[1] ? ft_strdup((char*)array[1]) : ft_strdup("");
	}
	while (array[i])
	{
		free((void*)array[i]);
		i++;
	}
	free((void*)array);
	free((void*)s);
	return (1);
}

static int	should_fork(unsigned short type)
{
	return (!(type == ST_LCD || type == ST_LPWD));
}

/*
** Loop and treat the input string while the user doesn't type 'quit' or press
** CTRL-D
*/

int		user_input_loop(t_config *config)
{
	char		*line;
	int			pid;
	t_packet	*packet;
	t_input		input;
	int			stat_loc;

	packet = (t_packet*)malloc(sizeof(t_packet)); // check malloc ret
	line = NULL;
	ft_putstr(PROMPT);
	while (gnl(0, &line) > 0)
	{
		treat_input(&input, line);
		if (input.cmd && !(input.cmd & T_MASK_CMD_LOCAL))
		{
			forge_packet(packet, (HEADER_SIZE + ft_strlen(input.arg)) << 16 | input.cmd, input.arg, 1);
			send_packet(config, packet);
			receive_cmd_packet(config, packet);
			if (switch_packet_type_client(config, packet) > 0)
				return (1);
			ft_bzero((char*)packet, packet->size);
			free(input.arg);
		}
		else if (input.cmd)
		{
			if (should_fork(packet->type) > 1)
			{
				pid = fork();
				if (pid == 0)
					exec_cmd_local(config, input.cmd);
				else
					wait4(pid, &stat_loc, 0, NULL);
			}
			else
			{
				exec_cmd_local_no_fork(config, &input);

			}
			free(input.arg);
		}
		ft_putstr(PROMPT);
	}
	free(packet);
	ft_putendl("Bye!");
	return (0);
}
