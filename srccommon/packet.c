#include <arpa/inet.h>
#include <stdlib.h>

#include "config.h"//
#include "packet.h"
#include "debug.h"//
#include "libftasm.h"
#include "libft.h"

static unsigned long int	my_swap64(unsigned long int n)
{
	return ((n & 0x00000000000000ff) << 56 |
		(n & 0x000000000000ff00) << 40 |
		(n & 0x0000000000ff0000) << 24 |
		(n & 0x00000000ff000000) << 8 |
		(n & 0x000000ff00000000) >> 8 |
		(n & 0x0000ff0000000000) >> 24 |
		(n & 0x00ff000000000000) >> 40 |
		(n & 0xff00000000000000) >> 56);
}

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
								char const* data, unsigned int chunks)
{
	// int size;
	// unsigned short type;

	// size = (unsigned short)(size_type >> 16);
	// type = (unsigned short)(size_type);
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

void	unforge_packet(t_packet *packet)
{
	packet->chunks_number = ntohl(packet->chunks_number);
	packet->magic = ntohl(packet->magic);
	packet->size = ntohs(packet->size);
	packet->type = ntohs(packet->type);
}

t_packet	*packetdup(t_config *config)
{
	// ft_putendl("packetdup");
	// if (!(new = (t_packet*)malloc(sizeof(t_packet))))
	// 	return (NULL);
	// ft_memcpy(new, packet, sizeof(MAX_PACKET_SIZE));
	// print_packet(packet, 1);
	// print_packet(new, 1);
	return ((t_packet*)config);
}
