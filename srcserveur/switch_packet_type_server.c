#include <stdlib.h>
#include <unistd.h>

#include "config.h"
#include "packet.h"
#include "send_message.h"
#include "exec_cmd.h"
#include "libft.h"//
#include "debug.h"//
#include "commands.h"

void	switch_packet_type_server(t_config *config, t_packet *packet)
{
	if (packet->type & T_MASK_CMD || packet->type & T_MASK_DATA)
	{
		if ((packet->type & ST_MASK) == ST_LS)
			ls(config);
		else if ((packet->type & ST_MASK) == ST_PWD)
			pwd(config, packet);
		else if (packet->type == (ASK_NEW_DATA_CONNECTION | ST_PUT))
			put(config, packet);
		else if (packet->type == (ASK_NEW_DATA_CONNECTION | ST_GET))
			get(config, packet);
		else
		{
			send_message(config, "ERROR: UNKNOWN CMD", "server");
			exit(0);
		}
	}
	else
	{
		send_message(config, "ERROR: UNKNOWN CMD", "server");
		exit(0);
	}
}

void	switch_packet_type_server_no_fork(t_config *config, t_packet *packet)
{
	if ((packet->type & ST_MASK) == ST_CD)
		cd(config, packet);
}
