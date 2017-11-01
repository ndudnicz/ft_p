#include <stdio.h>

#include "config.h"
#include "packet.h"

int		display_message_from_packet(t_packet *packet)
{
	// if (ft_strlen(packet->data))
		printf("%s\n", packet->data);
	return (0);
}
