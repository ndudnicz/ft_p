/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_get.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndudnicz <ndudnicz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 17:44:30 by ndudnicz          #+#    #+#             */
/*   Updated: 2017/11/01 17:44:31 by ndudnicz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "config.h"
#include "packet.h"
#include "debug.h"
#include "valid_filename.h"
#include "send_message.h"
#include "send_data.h"
#include "open_data_connection.h"
#include "error.h"

int		get(t_config *config, t_packet *packet)
{
	if (valid_filename(packet->data, 0) < 1)
		send_message(config, "ERROR: GET: FILE DOES NOT EXIST.", "server");
	else
		open_data_connection(config, packet, &send_data);
	exit(0);
}
