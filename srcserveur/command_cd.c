#include <stdlib.h>

#include "config.h"
#include "packet.h"
#include "send_message.h"

void	cd(t_config *config, t_packet *packet)
{
	send_message(config, "COUCOU", "server");
	exit(0);
}
