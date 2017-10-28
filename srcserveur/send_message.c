#include <unistd.h>

#include "libftasm.h"
#include "config.h"
#include "packet.h"
#include "send_packet.h"
#include "debug.h"//
#include "error.h"

int		send_message(t_config *config, char const *msg, char const *side)
{
	t_packet		hello;
	size_t const	size = (HEADER_SIZE + ft_strlen(msg)) << 16 | T_MESSAGE;

	forge_packet(&hello, size, msg, 1);
	if (send_packet(config->socket.cmd, &hello) > 0)
		return (ft_error(side, "send_message()", CANT_ESTABLISH_CONNECTION, 1));
	else
		return (0);
}
