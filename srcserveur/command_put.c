#include <stdlib.h>

#include "config.h"
#include "packet.h"
#include "debug.h"
#include "valid_filename.h"
#include "send_message.h"
#include "receive_data.h"
#include "open_data_connection.h"
#include "error.h"

int		put(t_config *config, t_packet *packet)
{
	if (!valid_filename(packet->data, 1))
		send_message(config, "ERROR: PUT: FILE ALREADY EXISTS.", "server");
	else
		open_data_connection(config, packet, &receive_data, &error_handler_socket);
	exit(0);
}
