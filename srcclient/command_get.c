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

#include "config.h"
#include "packet.h"
#include "debug.h"
#include "error.h"
#include "receive_data.h"
#include "my_syslimits.h"
#include "make_connection.h"
#include "libft.h"
#include "libftasm.h"
#include "options_handling.h"

int			get_check_local_file(char const *filename)
{
	char	cwd[PATH_MAX];
	char	*path;
	int		fd;

	if (!getcwd(cwd, PATH_MAX))
		return (ft_error("ERROR", "GET", "GETCWD()", 1));
	path = ft_strjoin_free(ft_strjoin(cwd, "/"), filename, 1, 0);
	if (!path)
		return (ft_error("ERROR", "GET", MALLOC_FAIL, 1));
	if ((fd = open(path, O_RDONLY)) > 0)
		return (ft_error("ERROR", "GET", "FILE ALREADY EXISTS.", 1));
	my_free(2, path);
	close(fd);
	return (0);
}

int			get(t_config *config, t_packet *packet, char const *filename)
{
	if (valid_port_string(packet->data))
		return (1);
	else
	{
		config->port.data = ft_atoi(packet->data);
		make_data_connection(config, filename, &receive_data);
		return (0);
	}
}
