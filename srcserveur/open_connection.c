#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netdb.h>

#include "error_master.h"
#include "config.h"
#include "packet.h"
#include "send_packet.h"
#include "send_message.h"
#include "libftasm.h"
#include "libft.h"
#include "constant_config_serveur.h"
#include "error_message.h"

static unsigned short	get_available_port(t_config *config, struct sockaddr_in *sin)
{
	unsigned short	port;

	port = LOW_BOUND_PORT_RANGE;
	while (port <= HIGH_BOUND_PORT_RANGE)
	{
		sin->sin_port = htons(port);
		if (bind(config->socket.data, (const struct sockaddr*)sin, sizeof(*sin)) < 0)
			port++;
		else
		{
			config->port.data = port;
			return (0);
		}
	}
	return (1);
}

/*
** Try to open a data connection on an available port, and send the new port
** to the client
** Return 0 if success
** Display an error message and return 1 if fail
*/

int		open_data_connection(t_config *config)
{
	struct protoent		*proto;
	struct sockaddr_in	sin;
	t_packet			new_connection;
	char				*new_port;

	valid_filename();
	if ((proto = getprotobyname("tcp")) == 0)
		return (send_message(config, INTERNAL_ERROR, "server"));
	if ((config->socket.data = socket(PF_INET, SOCK_STREAM, proto->p_proto)) < 0)
		return (send_message(config, INTERNAL_ERROR, "server"));
	sin.sin_family = AF_INET;
	if ((sin.sin_addr.s_addr = inet_addr(config->ip_str)) == INADDR_NONE)
		return (send_message(config, INTERNAL_ERROR, "server"));

	// HANDLE NO PORT AVAILABLE !
	if (get_available_port(config, &sin))
		return (send_message(config, INTERNAL_ERROR, "server"));

	if (listen(config->socket.server_master, LISTEN_MAX) < 0)
		return (send_message(config, INTERNAL_ERROR, "server"));
	config->inet_addr = sin.sin_addr.s_addr;
	if (!(new_port = ft_itoa((int)config->port.data)))
		return (ft_error("serveur", "", MALLOC_FAIL, 1));
	unsigned int size = (HEADER_SIZE | (unsigned short)ft_strlen(new_port)) << 16 | SEND_NEW_DATA_CONNECTION;
	forge_packet(&new_connection, size, new_port, 1);
	if (send_packet(config->socket.cmd, &new_connection) > 0)
		return (1);
	free(new_port);
	wait_for_connection();
	return (0);
}

/*
** Try to open a connection on <ip>:<port>, port given as parameter
** Return 0 if success
** Display an error message and return 1 if fail
*/

int		open_cmd_connection(t_config *config, char const *cmd_port_str)
{
	struct protoent		*proto;
	struct sockaddr_in	sin;

	sin.sin_port = htons(ft_atoi(cmd_port_str));
	printf("Opening connection on: %s:%d\n", config->ip_str, ntohs(sin.sin_port));
	if ((proto = getprotobyname("tcp")) == 0)
		return (ft_error("Serveur", "", GETPROTOBYNAME_FAIL, 1));
	if ((config->socket.server_master = socket(PF_INET, SOCK_STREAM, proto->p_proto)) < 0)
		return (ft_error("Serveur", "open_connection:", SOCKET_FAILED, 1));
	sin.sin_family = AF_INET;
	if ((sin.sin_addr.s_addr = inet_addr(config->ip_str)) == INADDR_NONE)
		return (ft_error("Serveur", "open_connection:", INET_ADDR_FAILED, 1));
	if (bind(config->socket.server_master, (const struct sockaddr*)&sin, sizeof(sin)) < 0)
		return (ft_error("Serveur", "open_connection:", CONNECT_ERROR, 1));
	if (listen(config->socket.server_master, LISTEN_MAX) < 0)
		return (ft_error("Serveur", "open_connection:", BIND_ERROR, 1));
	config->inet_addr = sin.sin_addr.s_addr;
	config->port.cmd = sin.sin_port;
	if (!(config->current_path = ft_strdup(".")))
		return (ft_error("serveur", "", MALLOC_FAIL, 1));
	printf("Connection opened on: %s:%d\n", config->ip_str, ntohs(config->port.cmd));
	return (0);
}
