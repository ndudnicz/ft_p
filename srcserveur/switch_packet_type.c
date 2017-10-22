#include <stdlib.h>
#include <unistd.h>
#include "packet.h"
#include "config.h"
#include "exec_cmd.h"
#include "my_pipe.h"
#include "libft.h"//
#include "debug.h"//

int		switch_packet_type(int sock, t_packet *packet)
{
	if (packet->type & T_MASK_CMD)
	{
		print_command_type(packet);
		my_pipe(STDOUT_FILENO, sock);
		my_pipe(STDERR_FILENO, sock);
		if (packet->type == (T_MASK_CMD | ST_LS))
		{
			execl("/bin/ls", "ls", ".", NULL);
		}
		return 0;
	}
	else
	{
		return 0;
	}
}
