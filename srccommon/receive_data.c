#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fcntl.h>

#include "config.h"
#include "packet.h"
#include "debug.h"//
#include "libft.h"//
#include "libftasm.h"
#include "send_packet.h"

int		receive_data(t_config *config, char const *filename)
{
	t_packet	*packet_ping;
	t_packet	packet_pong;
	int			r;
	int			fd;

	if ((fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0600)) < 0)
	{
		ft_putendl("Open() error");
		return (1);
	}
	ft_bzero(config->buf, MAX_PACKET_SIZE);
	while ((r = recv(config->socket.data, config->buf, MAX_PACKET_SIZE, 0)) > 0)
	{
		packet_ping = (t_packet*)config->buf;
		unforge_packet(packet_ping);
		if (packet_ping->magic == MAGIC && packet_ping->type == T_DATA)
		{
			write(fd, packet_ping->data, packet_ping->size - HEADER_SIZE);
			ft_putendl("PONG");
			forge_packet(&packet_pong, (HEADER_SIZE << 16 | T_PING_PONG), "", 1);
			send_packet(config->socket.data, &packet_pong);
		}
	}
	close(fd);
	if (config->options & DUPED)
		free(config);
	return (0);
}
