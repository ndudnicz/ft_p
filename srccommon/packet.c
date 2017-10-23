#include "packet.h"
#include "libftasm.h"
#include <arpa/inet.h>

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

unsigned long int	get_chunk_number(unsigned long int st_size)
{
	return ((st_size / (MAX_DATA_SIZE + 1)) + 1);
}

/*
** Normalize host values to network values
*/

void	forge_packet(t_packet *packet, unsigned int size_type,
								char const* data, unsigned long int st_size)
{
	unsigned short size;
	unsigned short type;

	size = (unsigned short)((size_type) >> 16);
	type = (unsigned short)(size_type);
	// printf("size_type:%08x\n", size_type);
	// printf("size:%hu\n", size);
	// printf("type:%hu\n", type);
	ft_bzero((char *)packet, MAX_PACKET_SIZE);
	packet->magic = htonl(MAGIC);
	if (packet->magic == htonl(MAGIC))
		packet->chunks_number = get_chunk_number(st_size);
	else
		packet->chunks_number = my_swap64(get_chunk_number(st_size));
	packet->size = htons(size);
	packet->type = htons(type);
	ft_memcpy(packet->data, data, size);
}

/*
** Get host values from network values
*/

void	unforge_packet(t_packet *packet)
{
	if (packet->magic != ntohl(MAGIC))
		packet->chunks_number = my_swap64(packet->chunks_number);
	packet->magic = ntohl(packet->magic);
	packet->size = ntohs(packet->size);
	packet->type = ntohs(packet->type);
}
