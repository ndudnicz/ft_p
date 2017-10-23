// #include <unistd.h>
#include <stdio.h>//

#include "config.h"
#include "packet.h"
#include "debug.h"//
#include "libft.h"
#include "libftasm.h"
#include "error_child.h"

int		receive_cmd_packet(t_config *config, t_packet *packet)
{
	int			ret;

	ft_bzero(config->buf, MAX_PACKET_SIZE);
	if ((ret = read(config->socket.cmd, config->buf, MAX_PACKET_SIZE)) < 0)
		ft_error_child("receive_cmd_packet", "read()", READ_FAIL);
	ft_memcpy(packet, config->buf, ret);
	unforge_packet(packet);
	return (0);
}
