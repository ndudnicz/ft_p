#include <unistd.h>
#include <stdlib.h>
#include <netdb.h>
#include <arpa/inet.h>

#include "config.h"
#include "packet.h"
#include "libftasm.h"
#include "libft.h"
#include "debug.h"//
#include "switch_packet_type.h"
#include "receive_packet.h"
#include "send_packet.h"
#include "error_child.h"
#include "error_master.h"

static int	say_hello(t_config *config)
{
	t_packet	hello;
	char const	*hi = "Serveur says hello !";
	int const	size = (HEADER_SIZE + ft_strlen(hi)) << 16 | T_MESSAGE;

	forge_packet(&hello, size, hi, 1);
	// print_forged_packet(&hello, 1);
	if (send_packet(config, &hello) > 0)
		return (ft_error("Serveur", "say_hello", CANT_ESTABLISH_CONNECTION, 1));
	else
	{
		// ft_putendl("c b");
		return (0);
	}
}

static int	child_waiting_loop(t_config *config)
{
	char				buf[MAX_PACKET_SIZE] = {0};
	int					r;
	t_packet			*packet;
	int		pid;

	pid = 0;
	// ft_putendl("s a");
	// receive_cmd_packet(config);
	// ft_putendl("s b");
	say_hello(config);
	ft_putendl("NEW CONNECTION ESTABLISHED!");
	while ((r = read(config->socket.cmd, buf, MAX_PACKET_SIZE)) > 0)
	{
		packet = (t_packet*)buf;
		// print_packet(packet, 1);
		if ((pid = fork()) < 0)
			ft_error_child("child_waiting_loop", "fork()", FORK_FAIL);
		else if (pid == 0)
			switch_packet_type(config->socket.cmd, packet);
		// else
		// 	ft_putstr("DONE");
		ft_bzero(buf, MAX_PACKET_SIZE);
	}
	close(config->socket.cmd);
	return (0);
}

int			master_waiting_loop(t_config *config)
{
	int		client_socket;
	int		pid;
	struct sockaddr_in	csin;
	unsigned int		cslen;
	t_config			*fork_config;

	pid = 0;
	while ((config->socket.cmd = accept(config->socket.server_master, (struct sockaddr*)&csin, &cslen)) > 0)
	{
		if ((pid = fork()) < 0)
		{
			ft_error_child("master_waiting_loop", "fork()", FORK_FAIL);
		}
		if (pid == 0)
		{
			if (!(fork_config = configcpy(config)))
				return (ft_error("master_waiting_loop", "configcpy", MALLOC_FAIL, 1));
			else
			{
				child_waiting_loop(fork_config);
			}
		}

	}
	close(config->socket.server_master);
	return (0);
}
