#include <unistd.h>

#include "config.h"
#include "packet.h"
#include "error_child.h"
#include "debug.h"//
#include "libft.h"//

/*
** Try to send the packet through the connection given in config.
** Return 0 if success.
** Display an error message and return 1 if fails.
*/

int		send_packet(t_config *config, t_packet *packet)
{
	int		ret;

	// ft_putendl("sending:");
	// print_forged_packet(packet, 1);
	ret = write(config->socket.cmd, packet, packet->size);
	if (ret < 0)
		ft_error_child(config->ip_addr_str, "sendpacket()", SEND_FAIL);
	return (ret < 0 ? 1 : 0);
}
