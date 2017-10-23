#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

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
		// ft_putendl("aaa");
		line = NULL;
		// char *join = ft_strdup("");
		// ft_putendl(tmp_file);
		// print_command_type(packet);
		my_pipe(STDOUT_FILENO, config->socket.cmd);
		my_pipe(STDERR_FILENO, config->socket.cmd);
		execl("/bin/ls", "ls", ".", NULL);
		// free(tmp_file);
		// send_message(config, "coucou", "server");
		// while (gnl(fd2, &line) > 0)
		// {
		// 	join  = ft_strjoin(join, line);
		// 	join  = ft_strjoin(join, "\n");
		// }
		// send_message(config, join, "server");
		// close(fd);
		// if (packet->type == (T_MASK_CMD | ST_LS))
		// {
		// }
		return 0;
	}
	else
	{
	// 	// print_packet(packet, 1);
	// 	send_message(config, ft_strjoin("server answer: ", packet->data), "server");
		return 0;
	}
}
