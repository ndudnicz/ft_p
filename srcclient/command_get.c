/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_get.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndudnicz <ndudnicz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 17:41:57 by ndudnicz          #+#    #+#             */
/*   Updated: 2017/11/01 17:41:59 by ndudnicz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#include "config.h"
#include "packet.h"
#include "debug.h"
#include "error.h"
#include "receive_data.h"
#include "my_syslimits.h"
#include "make_connection.h"
#include "libft.h"
#include "libftasm.h"

int			get_check_local_file(t_config *config, char const *filename)
{
	char	cwd[PATH_MAX];
	char	*path;
	int		fd;

	if (!getcwd(cwd, PATH_MAX))
		return (ft_error("ERROR", "GET", "GETCWD()", 1));
	path = ft_strjoin_free(ft_strjoin(cwd, "/"), filename, 1, 0);
	if (!path || (fd = open(path, O_RDONLY)) > 0)
	{
		my_free(1, path, config->options);
		return (ft_error("ERROR", "GET", "FILE ALREADY EXISTS.", 1));
	}
	my_free(2, path, config->options);
	close(fd);
	return (0);
}

int			get(t_config *config, t_packet *packet, char const *filename)
{
	config->port.data = ft_atoi(packet->data); //valid port string
	make_data_connection(config, filename, &receive_data);
	return (0);
}
