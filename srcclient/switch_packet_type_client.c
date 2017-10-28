#include <stdlib.h>

#include "config.h"
#include "packet.h"
#include "libft.h"
#include "libftasm.h"
#include "display_message.h"
#include "error.h"
#include "debug.h"//
#include "send_data.h"
#include "commands.h"

static int	cmd_handling(t_config *config, t_packet *packet)
{
	ft_putendl("cmd handling");
	print_packet(packet, 1);
	return (0);
}

static int	data_handling(t_config *config, t_packet *packet, char const *filename)
{
	// int			pid;
	// t_config	*fork_config;
	// int			stat_loc;


	ft_putendl("data handling");
	if (packet->type & ST_PUT)
		put(config, packet, filename, "");
	if (packet->type & ST_GET)
		put(config, packet, filename, "");
	return (0);
}

int		switch_packet_type_client_no_fork(t_config *config)
{
		return (0);

}

int		switch_packet_type_client(t_config *config, t_packet *packet, char const *arg)
{
	if (packet->magic != MAGIC)
	{
		ft_putstr(config->buf);
		return (0);
	}
	else if (packet->type == T_MESSAGE)
		return display_message_from_packet(packet);
	else if (packet->type == T_DATA)
		return 0;
	else if (packet->type == T_CLOSE_CONNECTION)
		return 0;
	// else if (packet->type & T_MASK_CMD)
		// return (cmd_handling(config, packet));
	else if (packet->type & SEND_NEW_DATA_CONNECTION)
		return (data_handling(config, packet, arg));
	else
		return (0);
}
