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
#include "packet.h"
#include "debug.h"//
#include "send_packet.h"
#include "receive_packet.h"
#include "switch_packet_type_client.h"
#include "error.h"//
#include "exec_cmd_local.h"
#include "commands.h"

static int	should_fork(unsigned short type)
{
	if (type == ST_LCD || type == ST_LPWD)
		return (0);
	else
		return (1);
}

void		fork_and_run(t_config *config, t_input *input)
{
	int			pid;
	int			stat_loc;
	
	if (should_fork(input->cmd) > 0)
	{
		pid = fork();
		if (pid == 0)
			exec_cmd_local(config, input->cmd);
		else
			wait4(pid, &stat_loc, 0, NULL);
	}
	else
		exec_cmd_local_no_fork(config, input);
}
/*
int		user_input_loop(t_config *config)
{
	char		*line;
	int			pid;
	t_packet	*packet;
	t_input		input;
	int			stat_loc;

	if (!(packet = (t_packet*)malloc(sizeof(t_packet))))
		return (ft_error("Error", "user_input_loop()", MALLOC_FAIL, 1));
	line = NULL;
	input.arg = NULL;
	while (ft_putstr(PROMPT) && gnl(0, &line) > 0)
	{
		if (input.arg)
			free(input.arg);
		if (treat_input(&input, line) == ST_QUIT)
			break ;
		if (input.arg && input.cmd && !(input.cmd & ST_CMD_LOCAL))
		{
			if ((input.cmd == ST_PUT && put_check_local_file(input.arg) > 0) ||
			(input.cmd == ST_GET && get_check_local_file(input.arg) > 0))
				continue ;
			forge_packet(packet, (HEADER_SIZE + ft_strlen(input.arg)) << 16 |
			input.cmd, input.arg, 1);
			send_packet(config->socket.cmd, packet);
			receive_packet(config, config->socket.cmd, packet);
			if (switch_packet_type_client(config, packet, input.arg) > 0)
				return (1);
			ft_bzero((char*)packet, packet->size);
		}
		else if (input.cmd)
			fork_and_run(config, &input);
	}
	free(packet);
	ft_putendl("Bye!");
	return (0);
}
*/
