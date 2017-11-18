/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_input_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndudnicz <ndudnicz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 17:42:59 by ndudnicz          #+#    #+#             */
/*   Updated: 2017/11/01 17:43:00 by ndudnicz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <unistd.h>

#include "config.h"
#include "user_input.h"
#include "packet.h"
#include "exec_cmd_local.h"

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
			exec_cmd_local(input->cmd, input->arg);
		else
			wait4(pid, &stat_loc, 0, NULL);
	}
	else
		exec_cmd_local_no_fork(config, input);
}
