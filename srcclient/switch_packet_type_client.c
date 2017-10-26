#include "config.h"
#include "packet.h"
#include "libft.h"
#include "libftasm.h"
#include "display_message.h"
#include "error_master.h"
#include "debug.h"//

static int	cmd_handling(t_config *config, t_packet *packet)
{
	print_packet(packet, 1);
	return (0);
}

static int	data_handling(t_config *config, t_packet *packet)
{
	print_packet(packet, 1);
	return (0);
}

int		switch_packet_type_client_no_fork(t_config *config)
{
		return (0);

}

int		switch_packet_type_client(t_config *config, t_packet *packet)
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
	else if (packet->type & T_MASK_CMD)
		return (cmd_handling(config, packet));
	else if (packet->type & T_MASK_DATA)
		return (data_handling(config, packet));
	else
		return (0);
}
