/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_packet.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndudnicz <ndudnicz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 17:44:10 by ndudnicz          #+#    #+#             */
/*   Updated: 2017/11/01 17:44:11 by ndudnicz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <arpa/inet.h>

#include "config.h"
#include "packet.h"
#include "error.h"

/*
** Try to send the packet through the connection given in config.
** Return 0 if success.
** Display an error message and return 1 if fails.
*/

int		send_packet(int const socket, t_packet *packet)
{
	int		ret;

	ret = write(socket, packet, ntohs(packet->size));
	if (ret < 0)
		ft_error_child("send_packet", "sendpacket()", SEND_FAIL);
	return (ret < 0 ? 1 : 0);
}
