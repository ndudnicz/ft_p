/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndudnicz <ndudnicz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 17:44:04 by ndudnicz          #+#    #+#             */
/*   Updated: 2017/11/01 17:44:05 by ndudnicz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <stdio.h>

#include "config.h"
#include "error.h"
#include "packet.h"
#include "send_packet.h"
#include "debug.h"
#include "libftasm.h"
#include "receive_packet.h"

static unsigned short	get_size(int const i, int const chunks_number,
								unsigned long int const file_size)
{
	if (i + 1 == chunks_number)
		return (HEADER_SIZE + file_size % MAX_DATA_SIZE);
	else
		return (MAX_PACKET_SIZE);
}

static int				ping_pong(t_config *config, t_packet *packet_ping,
									t_packet *packet_pong)
{
	send_packet(config->socket.data, packet_ping);
	receive_packet(config, config->socket.data, packet_pong, 0);
	return (0);
}

static int				chunk_data(t_config *config, char *data,
									int const chunks_number,
									unsigned long int const file_size)
{
	int				i;
	t_packet		*packet_ping;
	t_packet		*packet_pong;
	t_size_type		size_type;

	if (!(packet_ping = (t_packet*)malloc(sizeof(t_packet))) ||
	!(packet_pong = (t_packet*)malloc(sizeof(t_packet))))
		return (ft_error("Error", "send_data", MALLOC_FAIL, 1));
	i = 0;
	size_type.type = T_DATA;
	while (i < chunks_number)
	{
		ft_bzero((char*)packet_pong, sizeof(t_packet));
		size_type.size = get_size(i, chunks_number, file_size);
		forge_packet(packet_ping, &size_type, &data[i * MAX_DATA_SIZE],
		chunks_number);
		ping_pong(config, packet_ping, packet_pong);
		i++;
	}
	my_free(51, packet_ping);
	my_free(52, packet_pong);
	return (0);
}

int						ret_close(int fd1, int fd2, int ret)
{
	close(fd1);
	close(fd2);
	return (ret);
}

int						send_data(t_config *config, char const *filename,
									int fd)
{
	struct stat		stat;
	char			*data;
	int const		sock = config->socket.data;

	if ((fd = open(filename, O_RDONLY)) < 0)
		return (ft_error("ERROR", "send_data()", OPEN_FAILED, stop(sock)));
	if (fstat(fd, &stat) < 0)
		return (ft_error("ERROR", "send_data()", FSTAT_FAILED, stop(sock)));
	if ((data = (char*)mmap(NULL, stat.st_size, PROT_READ, MAP_PRIVATE, fd, 0))
	== MAP_FAILED)
	{
		close(fd);
		return (ft_error("ERROR", "send_data()", MMAP_FAILED,
		stop(config->socket.data)));
	}
	if (chunk_data(config, data, get_chunk_number(stat.st_size),
	stat.st_size) > 0)
		return (ret_close(fd, config->socket.data, 1));
	if (munmap(data, stat.st_size) < 0)
		ft_error_child("ERROR", "send_data()", MUNMAP_FAILED);
	return (ret_close(fd, config->socket.data, 0));
}
