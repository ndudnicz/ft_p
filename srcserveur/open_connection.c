#include <stdio.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "error_master.h"
#include "config.h"
#include "libftasm.h"
#include "constant_config_serveur.h"

/*
** Try to open a connection on 127.0.0.1:<port>, port given as parameter
** Return 0 if success
** Display an error message and return 1 if fail
*/

int		open_connection(t_config *config, char const *cmd_port_str)
{
	struct protoent		*proto;
	struct sockaddr_in	sin;

	printf("Opening connection on port: %s\n", cmd_port_str);
	proto = getprotobyname("tcp");
	if (proto == 0)
	{
		return (ft_error("Serveur", "", GETPROTOBYNAME_FAIL, 1));
	}
	config->socket.server_master = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(ft_atoi(cmd_port_str));
	sin.sin_addr.s_addr = inet_addr("127.0.0.1");
	if (bind(config->socket.server_master, (const struct sockaddr*)&sin, sizeof(sin)) < 0)
		return (ft_error("Serveur", "open_connection:", CONNECT_ERROR, 1));
	if (listen(config->socket.server_master, LISTEN_MAX) < 0)
		return (ft_error("Serveur", "open_connection:", BIND_ERROR, 1));
	config->inet_addr = sin.sin_addr.s_addr;
	config->port.cmd = sin.sin_port;
	if (!(config->current_path = ft_strdup(".")))
		return (ft_error("serveur", "", MALLOC_FAIL, 1));
	printf("Connection opened on port: %s\n", cmd_port_str);
	return (0);
}
