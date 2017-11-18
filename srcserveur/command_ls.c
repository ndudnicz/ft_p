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
#include "libftasm.h"
#include "libft.h"

static int	valid_arg(char const *arg)
{
	int			len;
	char const	*forbidden = "./\n\t\r\v\\rR";

	len = ft_strlen(arg) - 1;
	if (len > 0 && arg[0] != '-')
		return (1);
	while (len >= 0)
	{
		if (ft_strchr(forbidden, (int)arg[len]))
			return (1);
		len--;
	}
	return (0);
}

/*
** Pipe stdout and stderr in socket.cmd and execute /bin/ls -p current_path
*/

void		ls(t_config *config, char const *arg)
{
	my_pipe(STDOUT_FILENO, config->socket.cmd);
	my_pipe(STDERR_FILENO, config->socket.cmd);
	if (!valid_arg(arg) && ft_strlen(arg))
		execl(LS_PATH, LS_PATH, arg, ".", NULL);
	else
		execl(LS_PATH, LS_PATH, "-pa", ".", NULL);
}
