#include <unistd.h>
#include "config.h"
#include "packet.h"
#include "debug.h"//
#include "libft.h"

int		receive_cmd_packet(t_config *config)
{
	char		buf[MAX_PACKET_SIZE];
	int			ret;
	t_packet	*packet;

	buf[0] = 0;
	ret = read(config->socket.cmd, buf, MAX_PACKET_SIZE);
	packet = (t_packet*)buf;
	// unforge_packet(packet);
	if (packet->magic == MAGIC)
	{
		print_forged_packet(packet, 1);
	}
	else
		ft_putendl(buf);
	return (0);
}
