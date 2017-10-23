#include <unistd.h>
#include <stdlib.h>
#include <netdb.h>
#include <arpa/inet.h>

#include "config.h"
#include "packet.h"
#include "libftasm.h"
#include "libft.h"
#include "debug.h"//
#include "switch_packet_type_server.h"
#include "receive_packet.h"
#include "send_packet.h"
#include "send_message.h"
#include "error_child.h"
#include "error_master.h"

/*
** Send a welcome msg to the new client and wait for commands.
*/

static int	child_waiting_loop(t_config *config)
{
	char				buf[MAX_PACKET_SIZE] = {0};
	int					r;
	t_packet			*packet;
	int		pid;

	send_message(config, "Serveur says: Hello !", "Server");
	ft_putendl("NEW CONNECTION ESTABLISHED!");
	while ((r = read(config->socket.cmd, buf, MAX_PACKET_SIZE)) > 0)
	{
		pid = 0;
		packet = (t_packet*)buf;
		// print_packet(packet, 1);
		if ((pid = fork()) < 0)
			ft_error_child("child_waiting_loop", "fork()", FORK_FAIL);
		else if (pid == 0)
			switch_packet_type_server(config, packet);
		ft_bzero(buf, MAX_PACKET_SIZE);
	}
	close(config->socket.cmd);
	return (0);
}

/*
** Master loop, waiting for new input connection.
** fork(), copy *config and launch child_waiting_loop() when it gets
** a new connection
** Return 1 and display an error message if fails
*/

int			master_waiting_loop(t_config *config)
{
	int		client_socket;
	int		pid;
	struct sockaddr_in	csin;
	unsigned int		cslen;
	t_config			*fork_config;

	while ((config->socket.cmd = accept(config->socket.server_master, (struct sockaddr*)&csin, &cslen)) > 0)
	{
		pid = 0;
		if ((pid = fork()) < 0)
		{
			ft_error_child("master_waiting_loop", "fork()", FORK_FAIL);
		}
		if (pid == 0)
		{
			// while (config->pid == 0)
				// ft_putendl("wait");
			if (!(fork_config = configdup(config)))
				return (ft_error("master_waiting_loop", "configcpy", MALLOC_FAIL, 1));
			else
			{
				fork_config->tmp_file_str = ft_ltoa((long)fork_config);
				// printf("fork:  %s\n", );
				child_waiting_loop(fork_config);
			}
		}
		else
		{
			// printf("parent:%s\n", ft_ltoa((long)config));

			//  config->pid = pid;
				// printf("parent:%d\n", config->pid);
		}

	}
	close(config->socket.server_master);
	return (0);
}
