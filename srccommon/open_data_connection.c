#include <stdlib.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

#include "config.h"
#include "packet.h"
#include "error.h"
#include "send_packet.h"
#include "libftasm.h"
#include "libft.h"
#include "debug.h"//

static int				wait_for_client(t_config *config)
{
	struct sockaddr_in	csin;
	unsigned int		cslen;

	cslen = sizeof(csin);
	return (config->socket.data = accept(config->socket.data, (struct sockaddr*)&csin, &cslen));
}

/*
** Try to bind the new data socket on an available ephemeral port.
** Return 0 if success
** Return 1 if fails
*/

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

int		open_data_connection(t_config *config, /*char const *filename*/t_packet *packet,
					int (*transfert)(t_config*, char const*),
					int (*error_handler)(t_config*, char const*, char const*))
{
	struct protoent		*proto;
	struct sockaddr_in	sin;
	t_packet			new_connection;
	char				*new_port;

	if ((proto = getprotobyname("tcp")) == 0)
		return (error_handler(config, "open_data_connection()", INTERNAL_ERROR));
	if ((config->socket.data = socket(PF_INET, SOCK_STREAM, proto->p_proto)) < 0)
		return (error_handler(config, "open_data_connection()", INTERNAL_ERROR));
	sin.sin_family = AF_INET;
	if ((sin.sin_addr.s_addr = inet_addr(config->ip_str)) == INADDR_NONE)
		return (error_handler(config, "open_data_connection()", INTERNAL_ERROR));

	// HANDLE NO PORT AVAILABLE !
	if (get_available_port(config, &sin))
		return (error_handler(config, "open_data_connection()", INTERNAL_ERROR));

	if (listen(config->socket.data, 1) < 0)
		return (error_handler(config, "open_data_connection()", INTERNAL_ERROR));
	config->inet_addr = sin.sin_addr.s_addr;
	if (!(new_port = ft_itoa((int)config->port.data)))
		return (error_handler(config, "open_data_connection()", MALLOC_FAIL));
	unsigned int size_type = (HEADER_SIZE | (unsigned short)ft_strlen(new_port)) << 16 | SEND_NEW_DATA_CONNECTION | (packet->type & 0x0fff);
	forge_packet(&new_connection, size_type, new_port, 1);
	if (send_packet(config->socket.cmd, &new_connection) > 0)
		return (1);
	// print_forged_packet(packet, 0);
	free(new_port);
	wait_for_client(config);
	transfert(config, packet->data);
	return (0);
}
