/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_ls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndudnicz <ndudnicz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 17:44:34 by ndudnicz          #+#    #+#             */
/*   Updated: 2017/11/01 17:44:35 by ndudnicz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "config.h"
#include "my_pipe.h"

/*
** Pipe stdout and stderr in socket.cmd and execute /bin/ls -p current_path
*/

void	ls(t_config *config)
{
	// free_config(config);
	my_pipe(STDOUT_FILENO, config->socket.cmd);
	my_pipe(STDERR_FILENO, config->socket.cmd);
	execl(LS_PATH, LS_PATH, "-pa", ".", NULL);
}
