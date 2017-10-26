#include "config.h"
#include "packet.h"
#include "debug.h"
#include "open_connection.h"

int		put(t_config *config, t_packet *packet)
{
	open_data_connection(config);
	return (0);
}
