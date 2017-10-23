#include <stdio.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <stdlib.h>//

#include "error_master.h"
#include "config.h"
#include "libftasm.h"
#include "libft.h"
#include "packet.h"
#include "receive_packet.h"
#include "send_packet.h"
#include "switch_packet_type_client.h"
#include "debug.h"//

/*
** Try to establish a connection through the ip:port given as parameters.
** Set connection->socket if success.
** Return 0 if success
** Display an error and return 1 if fails.
*/

int			establish_connection(t_config *config, char const *ip_str,
								char const *cmd_port_str)
{
	struct protoent		*proto;
	struct sockaddr_in	sin;
	t_packet			*packet;

	packet = (t_packet*)malloc(sizeof(t_packet));//
	printf("Establishing connection to: %s:%s\n", ip_str, cmd_port_str);
	if ((proto = getprotobyname("tcp")) == 0)
		return (ft_error("Client", "", GETPROTOBYNAME_FAIL, 1));
	/*CONFIG INIT*/
	if ((config->socket.cmd = socket(PF_INET, SOCK_STREAM, proto->p_proto)) < 0)
		return (ft_error("Client", "open_connection:", SOCKET_FAILED, 1));
	if ((config->inet_addr = inet_addr("127.0.0.1")) == INADDR_NONE)
		return (ft_error("Client", "open_connection:", INET_ADDR_FAILED, 1));
	config->port.cmd = htons(ft_atoi(cmd_port_str));

	/*SIN INIT*/
	sin.sin_family = AF_INET;
	sin.sin_port = config->port.cmd;
	sin.sin_addr.s_addr = config->inet_addr;

	if (connect(config->socket.cmd, (const struct sockaddr*)&sin, sizeof(sin)) < 0)
		return (ft_error("Client", "establish_connection()", CONNECT_ERROR, 1));
	if (!(config->current_path = ft_strdup(".")))
		return (ft_error("Client", "", MALLOC_FAIL, 1));
	if (receive_cmd_packet(config, packet))
		return (1);
	// print_packet(packet, 1);
	if (switch_packet_type_client(config, packet) > 0)
		return (1);
	free(packet);
	printf("Connection done with: %s:%s\n", ip_str, cmd_port_str);
	return (0);
}
