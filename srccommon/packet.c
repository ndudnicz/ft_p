#include "packet.h"
#include "libftasm.h"
#include <arpa/inet.h>

void	forge_packet(unsigned short const size,
					unsigned short const type,
					char const *data,
					t_packet *packet)
{
	ft_bzero((char *)packet, MAX_PACKET_SIZE);
	packet->size = htons(size);
	packet->type = htons(type);
	ft_memcpy(packet->data, data, size);
}

void	unforge_packet(t_packet *packet)
{
	packet->size = ntohs(packet->size);
	packet->type = ntohs(packet->type);
}
