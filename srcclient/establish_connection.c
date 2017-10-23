#include <stdio.h>
#include <netdb.h>
#include <arpa/inet.h>

#include "error_master.h"
#include "config.h"
#include "libftasm.h"
#include "libft.h"
#include "packet.h"
#include "receive_packet.h"
#include "send_packet.h"

/*
** Say hello through the new established connection and wait for an answer.
** Return 0 if success.
** Display an error message and return 1 if fail.
*/

static int	say_hello(t_config *config)
{
	t_packet	hello;

	forge_packet(&hello, (HEADER_SIZE + 5) << 16 | T_MESSAGE, "hello", 1);
	if (send_packet(config, &hello) > 0)
		return (ft_error("Client", "say_hello", CANT_ESTABLISH_CONNECTION, 1));
	else
	{

		ft_putendl("c b");
		return (0);
	}
}

/*
** Try to establish a connection through the ip:port given as parameters.
** Set connection->socket if success.
** Display an error and return 1 if fails.
*/

int			establish_connection(t_config *config, char const *ip_str,
								char const *cmd_port_str)
{
	struct protoent		*proto;
	struct sockaddr_in	sin;

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
	if (receive_cmd_packet(config))
		return (1);
	printf("Connection done with: %s:%s\n", ip_str, cmd_port_str);
	return (0);
}
