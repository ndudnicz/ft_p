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
