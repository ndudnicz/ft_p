#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fcntl.h>

#include "config.h"
#include "packet.h"
#include "debug.h"
#include "libft.h"//
#include "libftasm.h"

int		receive_data(t_config *config, char const *filename)
{
	t_packet	*packet;
	int			r;
	int			fd;
	// char		*data;
	// int		i = 0;
	// int		index = 0;
	// char	*dup_filename = ft_strdup(filename);

	// data = NULL;
	if ((fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0600)) < 0)
	{
		ft_putendl("Open() error");
		return (1);
	}
	// while ((r = recv(config->socket.data, config->buf, MAX_PACKET_SIZE, MSG_PEEK)) > 0)
	while ((r = read(config->socket.data, config->buf, MAX_PACKET_SIZE)) > 0)
	{
		packet = (t_packet*)config->buf;
		unforge_packet(packet);
		print_packet(packet, 0);
		if (packet->magic == MAGIC && packet->type == T_DATA)
		{
			write(fd, packet->data, packet->size - HEADER_SIZE);
		}
	}
	close(fd);
	if (config->options & DUPED)
		free(config);
	return (0);
}
