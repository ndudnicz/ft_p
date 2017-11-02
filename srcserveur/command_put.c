/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_put.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndudnicz <ndudnicz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 17:44:38 by ndudnicz          #+#    #+#             */
/*   Updated: 2017/11/01 17:44:41 by ndudnicz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "config.h"
#include "packet.h"
#include "valid_filename.h"
#include "send_message.h"
#include "receive_data.h"
#include "open_data_connection.h"

int		put(t_config *config, t_packet *packet)
{
	if (valid_filename(config, packet->data, 1) < 1)
		send_message(config, "ERROR: PUT: FILE ALREADY EXISTS.", "server");
	else
		open_data_connection(config, packet, &receive_data);
	exit(0);
}
