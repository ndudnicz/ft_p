#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fcntl.h>
#include <stdio.h>

#include "config.h"
#include "packet.h"
#include "debug.h"//
#include "libft.h"//
#include "libftasm.h"
#include "send_packet.h"
#include "error.h"
#include "receive_packet.h"

static int	ret_error(t_config *config)
{
	ft_putendl("Open() error");
	close(config->socket.data);
	return (1);
}

static int	forge_and_send_pong(t_config *config, t_packet *packet_pong)
{
	t_size_type		size_type;

	size_type.size = HEADER_SIZE;
	size_type.type = T_PING_PONG;
	forge_packet(packet_pong, &size_type, "", 1);
	send_packet(config->socket.data, packet_pong);
	return (0);
}

int			receive_data(t_config *config, char const *filename)
{
	t_packet		*packet_ping;
	t_packet		packet_pong;
	int				fd;
	unsigned int	i;
	unsigned int	n;

	i = 1;
	if ((fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0600)) < 0)
		return (ret_error(config));
	ft_bzero(config->buf, MAX_PACKET_SIZE);
	// while (recv(config->socket.data, config->buf, MAX_PACKET_SIZE, 0) > 0)
	while (receive_packet(config, config->socket.data, packet_ping, 0) > 0)
	{
		// unforge_packet(packet_ping = (t_packet*)config->buf);
		if (packet_ping->magic == MAGIC && packet_ping->type == T_DATA)
		{
			n = packet_ping->chunks_number;
			write(fd, packet_ping->data, packet_ping->size - HEADER_SIZE);
			if (!(config->options & IAMSERVER))
				printf("%d / %d   size:%hu\n", i, packet_ping->chunks_number, packet_ping->size);
			forge_and_send_pong(config, &packet_pong);
			i++;
		}
	}
	ft_putnbr_endl(i);
	ft_putnbr_endl(n);
	// printf("i:%d  n:%d\n", i, n);
	if (i - 1 != n)
	{
		ft_error_child("ERROR", "DATA TRANSFERT", "CONNECTION LOST");
		exit(0);
	}
	close(fd);
	if (config->options & DUPED)
		my_free(50,config);
	return (0);
}
