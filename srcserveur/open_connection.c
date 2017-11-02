/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_connection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndudnicz <ndudnicz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 17:45:02 by ndudnicz          #+#    #+#             */
/*   Updated: 2017/11/01 17:45:04 by ndudnicz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netdb.h>

#include "config.h"
#include "packet.h"
#include "send_packet.h"
#include "send_message.h"
#include "libftasm.h"
#include "libft.h"
#include "constant_config_serveur.h"
#include "error.h"
#include "debug.h"

/*
** Try to open a connection on <ip>:<port>, port given as parameter
** Return 0 if success
** Display an error message and return 1 if fail
*/

int						open_cmd_connection(t_config *config,
											char const *cmd_port_str)
{
	struct protoent		*proto;
	struct sockaddr_in	sin;

	sin.sin_port = htons((unsigned short)ft_atoi(cmd_port_str));
	printf("Opening connection on: %s:%d\n", config->ip_str,
	ntohs(sin.sin_port));
	if ((proto = getprotobyname("tcp")) == 0)
		return (ft_error("Serveur", "", GPBN_FAIL, 1));
	if ((config->socket.server_master =
	socket(PF_INET, SOCK_STREAM, proto->p_proto)) < 0)
		return (ft_error("Serveur", "open_connection:", SOCKET_FAILED, 1));
	sin.sin_family = AF_INET;
	if ((sin.sin_addr.s_addr = inet_addr(config->ip_str)) == INADDR_NONE)
		return (ft_error("Serveur", "open_connection:", INET_ADDR_FAILED, 1));
	if (bind(config->socket.server_master, (const struct sockaddr*)&sin,
	sizeof(sin)) < 0)
		return (ft_error("Serveur", "open_connection:", CONNECT_ERROR, 1));
	if (listen(config->socket.server_master, LISTEN_MAX) < 0)
		return (ft_error("Serveur", "open_connection:", BIND_ERROR, 1));
	config->inet_addr = sin.sin_addr.s_addr;
	config->port.cmd = sin.sin_port;
	printf("Connection opened on: %s:%d\n", config->ip_str,
	ntohs(config->port.cmd));
	return (0);
}

static int				wait_for_client(t_config *config)
{
	struct sockaddr_in	csin;
	unsigned int		cslen;

	cslen = sizeof(csin);
	return (config->socket.data = accept(config->socket.data,
	(struct sockaddr*)&csin, &cslen));
}

/*
** Try to bind the new data socket on an available ephemeral port.
** Return 0 if success
** Return 1 if fails
*/

static unsigned int	get_available_port(t_config *config,
											struct sockaddr_in *sin)
{
	unsigned int	port;

	port = LOW_BOUND_PORT_RANGE;
	while (port <= HIGH_BOUND_PORT_RANGE)
	{
		sin->sin_port = htons(port);
		if (bind(config->socket.data, (const struct sockaddr*)sin, sizeof(*sin))
		< 0)
			port++;
		else
		{
			config->port.data = port;
			return (0);
		}
	}
	return (1);
}

static int				open_data_norme(t_config *config,
										struct sockaddr_in *sin)
{
	if ((sin->sin_addr.s_addr = inet_addr(config->ip_str)) == INADDR_NONE)
		return (send_message(config, "open_data_connection()", INTERNAL_ERROR));
	if (get_available_port(config, sin))
		return (send_message(config, "open_data_connection()", INTERNAL_ERROR));
	if (listen(config->socket.data, 1) < 0)
		return (send_message(config, "open_data_connection()", INTERNAL_ERROR));
	config->inet_addr = sin->sin_addr.s_addr;
	return (0);
}

/*
** Try to open a data connection on an available port, and send the new port
** to the client
** Return 0 if success
** Display an error message and return 1 if fail
*/

int						open_data_connection(t_config *config, t_packet *packet,
								int (*transfert)(t_config*, char const*, int))
{
	struct protoent		*proto;
	struct sockaddr_in	sin;
	t_packet			new_connection;
	char				*new_port;
	t_size_type			size_type;

	if ((proto = getprotobyname("tcp")) == 0)
		return (send_message(config, "open_data_connection()", INTERNAL_ERROR));
	if ((config->socket.data = socket(PF_INET, SOCK_STREAM, proto->p_proto))
	< 0)
		return (send_message(config, "open_data_connection()", INTERNAL_ERROR));
	sin.sin_family = AF_INET;
	if (open_data_norme(config, &sin))
		return (1);
	if (!(new_port = ft_itoa((int)config->port.data)))
		return (send_message(config, "open_data_connection()", MALLOC_FAIL));
	size_type.size = HEADER_SIZE + ft_strlen(new_port);
	size_type.type = SEND_NEW_DATA_CONNECTION | (packet->type & ST_MASK);
	forge_packet(&new_connection, &size_type, new_port, 1);
	if (send_packet(config->socket.cmd, &new_connection) > 0)
		return (1);
	my_free(29, new_port, config->options);
	wait_for_client(config);
	transfert(config, packet->data, 0);
	return (0);
}
