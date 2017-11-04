/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_local.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndudnicz <ndudnicz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 17:42:36 by ndudnicz          #+#    #+#             */
/*   Updated: 2017/11/01 17:42:37 by ndudnicz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <unistd.h>
#include <stdlib.h>

#include "config.h"
#include "packet.h"
#include "user_input.h"
#include "commands.h"

void	exec_cmd_local(unsigned short cmd)
{
	if ((cmd & ST_MASK) == ST_LLS)
		lls();
	else
		exit(0);
}

int		exec_cmd_local_no_fork(t_config *config, t_input *input)
{
	if (input->cmd == ST_LCD)
		return (lcd(config, input->arg));
	else if (input->cmd == ST_LPWD)
		return (lpwd());
	else
		return (0);
}
