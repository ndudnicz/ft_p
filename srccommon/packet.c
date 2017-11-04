/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   packet.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndudnicz <ndudnicz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 17:43:41 by ndudnicz          #+#    #+#             */
/*   Updated: 2017/11/01 17:43:42 by ndudnicz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <arpa/inet.h>
//#include <stdlib.h>

#include "packet.h"
#include "libftasm.h"

/*
** Get st_size from struct stat (sys/stat.h) and return a number of chunk
** that need to be sent
*/

unsigned int	get_chunk_number(unsigned long int st_size)
{
	return ((unsigned int)((st_size / (MAX_DATA_SIZE)) + 1));
}

/*
** Normalize host values to network values
*/

void			forge_packet(t_packet *packet, t_size_type const *size_type,
								char const *data, unsigned int chunks)
{
	ft_bzero((char *)packet, MAX_PACKET_SIZE);
	packet->magic = htonl(MAGIC);
	packet->chunks_number = htonl(chunks);
	packet->size = htons(size_type->size);
	packet->type = htons(size_type->type);
	ft_memcpy(packet->data, data, size_type->size - HEADER_SIZE);
}

/*
** Get host values from network values
*/

void			unforge_packet(t_packet *packet)
{
	packet->chunks_number = ntohl(packet->chunks_number);
	packet->magic = ntohl(packet->magic);
	packet->size = ntohs(packet->size);
	packet->type = ntohs(packet->type);
}
