#include <unistd.h>
#include <arpa/inet.h>//
#include <sys/socket.h>

#include "config.h"//
#include "packet.h"
#include "debug.h"//
#include "libft.h"//
#include "error.h"

/*
** Try to send the packet through the connection given in config.
** Return 0 if success.
** Display an error message and return 1 if fails.
*/

int		send_packet(int const socket, t_packet *packet)
{
	int		ret;

	ret = send(socket, packet, ntohs(packet->size), 0);
	// ft_putendl("send_packet ---->");
	// print_forged_packet(packet, 0);
	// ret = write(socket, packet, packet->size);
	if (ret < 0)
		ft_error_child("send_packet", "sendpacket()", SEND_FAIL);
	return (ret < 0 ? 1 : 0);
}
