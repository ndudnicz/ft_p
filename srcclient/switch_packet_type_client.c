/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch_packet_type_client.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndudnicz <ndudnicz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 17:42:45 by ndudnicz          #+#    #+#             */
/*   Updated: 2017/11/01 17:42:46 by ndudnicz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"
#include "packet.h"
#include "display_message.h"
#include "commands.h"

static int	data_handling(t_config *config, t_packet *packet,
							char const *filename)
{
	if ((packet->type & ST_MASK) == (ST_PUT & ST_MASK))
		return (put(config, packet, filename));
	else if ((packet->type & ST_MASK) == (ST_GET & ST_MASK))
		return (get(config, packet, filename));
	else
		return (0);
}

int			switch_packet_type_client(t_config *config, t_packet *packet,
		char const *arg)
{
	if (packet->magic != MAGIC)
		return (0);
	else if (packet->type == T_MESSAGE)
		return (display_message_from_packet(packet));
	else if ((packet->type & 0xf000) == SEND_NEW_DATA_CONNECTION)
		return (data_handling(config, packet, arg));
	else
		return (0);
}
