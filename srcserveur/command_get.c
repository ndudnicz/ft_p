#include "config.h"
#include "packet.h"
#include "debug.h"
#include "valid_filename.h"
#include "send_message.h"
#include "receive_data.h"
#include "open_data_connection.h"
#include "error.h"

int		get(t_config *config, t_packet *packet)
{
	if (!valid_filename(packet->data, 0))
		return (send_message(config, "ERROR: FILE DOES NOT EXIST.", "server"));
	else
		open_data_connection(config, packet, &receive_data, &error_handler_socket);
	return (0);
}
