/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_put.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndudnicz <ndudnicz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 17:42:20 by ndudnicz          #+#    #+#             */
/*   Updated: 2017/11/01 17:42:21 by ndudnicz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "config.h"
#include "packet.h"
#include "debug.h"
#include "error.h"
#include "send_data.h"
#include "my_syslimits.h"
#include "make_connection.h"
#include "libft.h"
#include "libftasm.h"
#include "options_handling.h"
#include "send_packet.h"

int		put_check_local_file(char const *filename)
{
	char		cwd[PATH_MAX];
	char		*path;
	int			fd;
	struct stat	stat;

	path = NULL;
	if (!getcwd(cwd, PATH_MAX))
		return (ft_error("ERROR", "PUT", "getcwd()", 1));
	path = ft_strjoin_free(ft_strjoin(cwd, "/"), filename, 1, 0);
	if (!path || (fd = open(path, O_RDONLY)) < 0)
	{
		my_free(10, path);
		return (ft_error("ERROR", "PUT", INVALID_PATH, 1));
	}
	if (fstat(fd, &stat) < 0)
		return (ft_error("ERROR", "PUT", FSTAT_FAILED, 1));
	if (!(stat.st_mode & S_IFREG))
		return (ft_error("ERROR", "PUT", INVALID_FILE, 1));
	my_free(11, path);
	close(fd);
	return (0);
}

int		put(t_config *config, t_packet *packet, char const *filename)
{
	if (valid_port_string(packet->data))
		return (1);
	else
	{
		config->port.data = ft_atoi(packet->data);
		make_data_connection(config, filename, &send_data);
		return (0);
	}
}
