/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_message.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndudnicz <ndudnicz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 17:45:08 by ndudnicz          #+#    #+#             */
/*   Updated: 2017/11/01 17:45:09 by ndudnicz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "libftasm.h"
#include "config.h"
#include "packet.h"
#include "send_packet.h"
#include "debug.h"//
#include "error.h"

int		send_message(t_config *config, char const *msg, char const *side)
{
	t_packet		hello;
	// size_t const	size = (HEADER_SIZE + ft_strlen(msg)) << 16 | T_MESSAGE;
	t_size_type const	size_type = {HEADER_SIZE + ft_strlen(msg), T_MESSAGE};

	forge_packet(&hello, &size_type, msg, 1);
	if (send_packet(config->socket.cmd, &hello) > 0)
		return (ft_error(side, "send_message()", CANT_ESTABLISH_CONNECTION, 1));
	else
		return (0);
}
