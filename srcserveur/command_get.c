#include <stdlib.h>

#include "config.h"
#include "packet.h"
#include "debug.h"
#include "valid_filename.h"
#include "send_message.h"
#include "send_data.h"
#include "open_data_connection.h"
#include "error.h"

int		get(t_config *config, t_packet *packet)
{
	if (!valid_filename(packet->data, 0))
		send_message(config, "ERROR: GET: FILE DOES NOT EXIST.", "server");
	else
		open_data_connection(config, packet, &send_data, &error_handler_socket);
	exit(0);
}
