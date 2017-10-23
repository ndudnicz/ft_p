#include "config.h"
#include "packet.h"
#include "libft.h"
#include "libftasm.h"
#include "display_message.h"
#include "error_master.h"
#include "debug.h"//

static int	cmd_handling(t_config *config, t_packet *packet)
{
	ft_putstr("COMMAND HANDLING\n");
	return (0);
}

static int	data_handling(t_config *config, t_packet *packet)
{
	ft_putstr("DATA HANDLING\n");
	return (0);
}

int		switch_packet_type_client(t_config *config, t_packet *packet)
{
	if (packet->magic != MAGIC)
	{
		ft_putendl(config->buf);
		return (0);
	}
		// return (ft_error("Client", "switch_received_packet()", BAD_PACKET, 1));
	else if (packet->type == T_MESSAGE)
	{
		return display_message_from_packet(packet);

	}
	else if (packet->type == T_DATA)
	{
		ft_putstr("DATA PACKET HANDLING\n");
		return 0;
	}
	else if (packet->type == T_CLOSE_CONNECTION)
	{
		ft_putstr("CLOSE CONNECTION\n");
		return 0;
	}
	else if (packet->type & T_MASK_CMD)
		return (cmd_handling(config, packet));
	else if (packet->type & T_MASK_DATA)
		return (data_handling(config, packet));
	else
	{
		ft_putendl(config->buf);
		return (0);
	}
		// return (ft_error("Client", "switch_received_packet()", BAD_TYPE, 1));
}
