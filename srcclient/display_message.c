/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_message.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndudnicz <ndudnicz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 17:42:26 by ndudnicz          #+#    #+#             */
/*   Updated: 2017/11/01 17:42:27 by ndudnicz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "config.h"
#include "packet.h"

int		display_message_from_packet(t_packet *packet)
{
	// if (ft_strlen(packet->data))
		printf("%s\n", packet->data);
	return (0);
}
