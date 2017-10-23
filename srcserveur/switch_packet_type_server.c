#include <stdlib.h>
#include <unistd.h>

#include "packet.h"
#include "config.h"
#include "send_message.h"
#include "exec_cmd.h"
#include "my_pipe.h"
#include "libft.h"//
#include "debug.h"//


int		switch_packet_type_server(t_config *config, t_packet *packet)
{
	if (packet->type & T_MASK_CMD)
	{
		// print_command_type(packet);
		// my_pipe(STDOUT_FILENO, sock);
		// my_pipe(STDERR_FILENO, sock);
		// if (packet->type == (T_MASK_CMD | ST_LS))
		// {
			// execl("/bin/ls", "ls", ".", NULL);
		// }
		return 0;
	}
	else
	{
		// print_packet(packet, 1);
		send_message(config, ft_strjoin("server answer: ", packet->data), "server");
		return 0;
	}
}
