#include "packet.h"
#include "libftasm.h"
#include <arpa/inet.h>

/*
** Get st_size from struct stat (sys/stat.h) and return a number of chunk
** that need to be sent
*/

unsigned long int	get_chunk_number(unsigned long int st_size)
{
	return ((st_size / (MAX_DATA_SIZE + 1)) + 1);
}

/*
** Normalize host values to network values
*/

void	forge_packet(unsigned short const size, unsigned short const type,
					char const *data, t_packet *packet,
					unsigned long int st_size)
{
	ft_bzero((char *)packet, MAX_PACKET_SIZE);
	packet->magic = htonl(MAGIC);
	packet->chunks_number = get_chunk_number(st_size);
	packet->chunks_number = ((unsigned long)htonl(packet->chunks_number >> 32) << 32) + htonl((int)packet->chunks_number);
	packet->size = htons(size);
	packet->type = htons(type);
	ft_memcpy(packet->data, data, size);
}

/*
** Get host values from network values
*/

void	unforge_packet(t_packet *packet)
{
	packet->magic = ntohl(packet->magic);
	packet->chunks_number = ((unsigned long)ntohl(packet->chunks_number >> 32) << 32) + ntohl((int)packet->chunks_number);
	packet->size = ntohs(packet->size);
	packet->type = ntohs(packet->type);
}
