#include <unistd.h>
#include <stdlib.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <stdio.h>

#include "config.h"
#include "packet.h"
#include "libftasm.h"
#include "libft.h"
#include "debug.h"//
#include "switch_packet_type_server.h"
#include "receive_packet.h"
#include "send_packet.h"
#include "send_message.h"
#include "error.h"

static int	should_fork(unsigned short type)
{
	return (!(type == ST_CD));
}

/*
** Send a welcome msg to the new client and wait for commands.
** Fork a new process that will execute the command and wait4 until the
** child process exits
*/

static int	child_waiting_loop(t_config *config)
{
	int			r;
	t_packet	*packet;
	int			pid;
	int			stat_loc;
	t_config	*fork_config;

	send_message(config, "Server says: Hello !", "Server");
	ft_putendl("NEW CONNECTION ESTABLISHED!");
	while ((r = recv(config->socket.cmd, config->buf, MAX_PACKET_SIZE, 0)) > 0)
	{
		pid = 0;
		packet = (t_packet*)config->buf;
		unforge_packet(packet);
		if (should_fork(packet->type))
		{
			if ((pid = fork()) < 0 || !(fork_config = configdup(config)))
				ft_error_child("child_waiting_loop", "fork()", FORK_FAIL);
			else if (pid == 0)
				switch_packet_type_server(fork_config, packet);
			else
				wait4(pid, &stat_loc, 0, NULL);
		}
		else
			switch_packet_type_server_no_fork(config, packet);
		ft_bzero(config->buf, MAX_PACKET_SIZE);
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
	int					pid;
	struct sockaddr_in	csin;
	unsigned int		cslen = sizeof(csin);
	t_config			*fork_config;
	int					stat_loc;

	while ((config->socket.cmd = accept(config->socket.server_master, (struct sockaddr*)&csin, &cslen)))
	{
		pid = 0;
		if ((pid = fork()) < 0)
			ft_error_child("master_waiting_loop", "fork()", FORK_FAIL);
		if (config->socket.cmd > 0 && pid == 0)
		{
			if (!fork())
			{
				if (!(fork_config = configdup(config)))
				{
					ft_error_child("master_waiting_loop", "configcpy", MALLOC_FAIL);
					exit(0);
				}
				else
					child_waiting_loop(fork_config);
				free_config(config);
				exit(0);
			}
			else
				exit(0);
		}
		else if (config->socket.cmd > 0 && pid)
			wait4(pid, &stat_loc, 0, NULL);
		if (config->socket.cmd < 0)
			printf("Accept() error, exit.\n");
		// return 0;
	}
	close(config->socket.server_master);
	return (0);
}
