#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>//

#include "packet.h"
#include "config.h"
#include "send_message.h"
#include "exec_cmd.h"
#include "libft.h"//
#include "debug.h"//
#include "commands.h"

void	switch_packet_type_server(t_config *config, t_packet *packet)
{
	print_packet(packet, 1);
	if (packet->type & T_MASK_CMD || packet->type & T_MASK_DATA)
	{
		if (packet->type == ST_LS)
			ls(config);
		else if (packet->type == ST_PWD)
			pwd(config, packet);
		else if (packet->type == ASK_NEW_DATA_CONNECTION)
			put(config, packet);
		else
			exit(0);
	}
	else
		exit(0);
}

void	switch_packet_type_server_no_fork(t_config *config, t_packet *packet)
{
	if (packet->type & T_MASK_CMD)
	{
		if (packet->type == ST_CD)
			cd(config, packet);
	}
}
