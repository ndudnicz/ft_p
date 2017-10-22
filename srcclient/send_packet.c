#include "packet.h"
#include "config.h"
#include <unistd.h>
#include "error_child.h"

/*
** Try to send the packet to through the connection given in config.
** Return 0 if success.
** Display an error message and return 1 if fail.
*/

int		send_packet(t_config *config, t_packet *packet)
{
	int		ret;

	ret = write(config->socket.cmd, packet, packet->size);
	if (ret < 0)
		ft_error_child(config->ip_addr_str, "sendpacket()", SEND_FAIL);
	return (ret < 0 ? 1 : 0);
}
