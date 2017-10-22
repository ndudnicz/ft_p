#include "error_master.h"
#include <stdio.h>
#include "config.h"
#include <arpa/inet.h>
#include "libftasm.h"
#include <netdb.h>

/*
** Try to establish a connection through the ip:port given as parameters.
** Set connection->socket if success.
** Display an error and return 1 if fails.
*/

int		establish_connection(t_config *config, char const *ip_str,
								char const *cmd_port_str)
{
	struct protoent		*proto;
	struct sockaddr_in	sin;

	printf("Establishing connection to: %s:%s\n", ip_str, cmd_port_str);
	proto = getprotobyname("tcp");
	if (proto == 0)
	{
		return (-1);
	}
	/*CONFIG INIT*/
	config->socket.cmd = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	config->inet_addr = inet_addr(ip_str);
	config->port.cmd = htons(ft_atoi(cmd_port_str));//sin.sin_port;

	/*SIN INIT*/
	sin.sin_family = AF_INET;
	sin.sin_port = config->port.cmd;
	sin.sin_addr.s_addr = config->inet_addr;

	if (connect(config->socket.cmd, (const struct sockaddr*)&sin, sizeof(sin)) < 0)
		return (ft_error("Client", "establish_connection()", CONNECT_ERROR, 1));
	if (!(config->current_path = ft_strdup(".")))
		return (ft_error("client", "", MALLOC_FAIL, 1));
	printf("Connection done with: %s:%s\n", ip_str, cmd_port_str);
	return (0);
}
