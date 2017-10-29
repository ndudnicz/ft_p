// #include <unistd.h>
#include <stdio.h>//
#include <sys/socket.h>

#include "config.h"
#include "packet.h"
#include "debug.h"//
#include "libft.h"
#include "libftasm.h"
#include "error.h"

int		receive_packet(t_config *config, int socket, t_packet *packet)
{
	int			ret;

	ft_bzero(config->buf, MAX_PACKET_SIZE);
	if ((ret = recv(socket, config->buf, MAX_PACKET_SIZE, 0)) < 0)
	// if ((ret = read(socket, config->buf, MAX_PACKET_SIZE)) < 0)
		ft_error_child("receive_cmd_packet", "read()", READ_FAIL);
	ft_memcpy(packet, config->buf, ret);
	unforge_packet(packet);
	return (0);
}
