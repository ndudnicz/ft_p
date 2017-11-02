/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   establish_connection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndudnicz <ndudnicz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 17:42:31 by ndudnicz          #+#    #+#             */
/*   Updated: 2017/11/01 17:42:32 by ndudnicz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <stdlib.h>

#include "config.h"
#include "libftasm.h"
#include "packet.h"
#include "receive_packet.h"
#include "switch_packet_type_client.h"
#include "debug.h"
#include "error.h"

static int	make_socket(t_config *config, char const *ip_str)
{
	struct protoent		*proto;

	if ((proto = getprotobyname("tcp")) == 0)
		return (ft_error("Client", "", GPBN_FAIL, 1));
	if ((config->socket.cmd = socket(PF_INET, SOCK_STREAM, proto->p_proto)) < 0)
		return (ft_error("Client", "open_connection:", SOCKET_FAILED, 1));
	if ((unsigned int)(config->inet_addr = inet_addr(ip_str)) == INADDR_NONE)
		return (ft_error("Client", "open_connection:", INET_ADDR_FAILED, 1));
	return (0);
}

/*
** Try to make a command connection through the ip:port
** given as parameters.
** Return 0 if success
** Display an error and return 1 if fails.
*/

int			make_connection(t_config *config, char const *ip_str,
								char const *cmd_port_str)
{
	struct sockaddr_in	sin;
	t_packet			*packet;

	if (!(packet = (t_packet*)malloc(sizeof(t_packet))))
		return (ft_error("Client", "make_connection()", MALLOC_FAIL, 1));
	printf("Connecting to: %s:%s\n", ip_str, cmd_port_str);
	make_socket(config, ip_str);
	config->port.cmd = htons(ft_atoi(cmd_port_str));
	sin.sin_family = AF_INET;
	sin.sin_port = config->port.cmd;
	sin.sin_addr.s_addr = config->inet_addr;
	if (connect(config->socket.cmd, (const struct sockaddr*)&sin, sizeof(sin))
	< 0)
		return (ft_error("Client", "make_connection()", CONNECT_ERROR, 1));
	receive_packet(config, config->socket.cmd, packet, 0);
	if (switch_packet_type_client(config, packet, NULL) > 0)
		return (1);
	my_free(12, packet);
	printf("Connection done with: %s:%s\n", ip_str, cmd_port_str);
	return (0);
}

/*
** Try to make a data connection through the new port
** given as parameters, by the server.
** Return 0 if success
** Display an error and return 1 if fails.
*/

int			make_data_connection(t_config *config, char const *filename,
				int (*transfert)(t_config*, char const*, int))
{
	struct protoent		*proto;
	struct sockaddr_in	sin;

	if ((proto = getprotobyname("tcp")) == 0)
		return (ft_error("ERROR", "make_data_connection()", GPBN_FAIL, 0));
	if ((config->socket.data = socket(PF_INET, SOCK_STREAM, proto->p_proto))
	< 0)
		return (ft_error("ERROR", "make_data_connection()", SOCKET_FAILED, 0));
	config->port.data = htons(config->port.data);
	sin.sin_family = AF_INET;
	sin.sin_port = config->port.data;
	sin.sin_addr.s_addr = config->inet_addr;
	if (connect(config->socket.data, (const struct sockaddr*)&sin, sizeof(sin))
	< 0)
		return (ft_error("ERROR", "establish_connection()", CONNECT_ERROR, 0));
	printf("Starting transfert ...\n");
	if (!transfert(config, filename, 0))
		printf("Transfert done.\n");
	return (0);
}
