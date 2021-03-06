/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiting_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndudnicz <ndudnicz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 17:45:24 by ndudnicz          #+#    #+#             */
/*   Updated: 2017/11/01 17:45:25 by ndudnicz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
#include "switch_packet_type_server.h"
#include "receive_packet.h"
#include "send_packet.h"
#include "send_message.h"
#include "error.h"

static void	ft_norme(t_config *config, t_packet *packet, int const ret)
{
	ft_bzero((char*)packet, MAX_PACKET_SIZE);
	if (ret > MAX_PACKET_SIZE)
		exit(0);
	ft_memcpy(packet, config->buf, ret);
	unforge_packet(packet);
	ft_bzero(config->buf, MAX_PACKET_SIZE);
}

static void	my_fork_child(t_config *config, t_packet *packet)
{
	int		pid;
	int		stat_loc;

	if ((pid = fork()) < 0)
		ft_error_child("child_waiting_loop", "fork()", FORK_FAIL);
	else if (pid == 0)
		switch_packet_type_server(config, packet);
	else
		wait4(pid, &stat_loc, 0, NULL);
}

/*
** Send a welcome msg to the new client and wait for commands.
** Fork a new process that will execute the command and wait4 until the
** child process exits
*/

static int	child_waiting_loop(t_config *config)
{
	t_packet	*packet;
	int			ret;

	if (!(packet = (t_packet*)malloc(sizeof(t_packet))))
	{
		stop(config->socket.cmd, "ERROR: INTERNAL ERROR: CLOSING CONNECTION.");
		close(config->socket.cmd);
		exit(0);
	}
	else
		send_message(config, "Server says: Hello !", "Server");
	while ((ret = recv(config->socket.cmd, config->buf, MAX_PACKET_SIZE, 0))
	> 0)
	{
		config->buf[ret] = 0;
		ft_norme(config, packet, ret);
		if (packet->type != ST_CD)
			my_fork_child(config, packet);
		else
			switch_packet_type_server_no_fork(config, packet);
	}
	exit(0);
}

static void	my_fork_master(t_config *config)
{
	if (!fork())
		child_waiting_loop(config);
	else
		exit(0);
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
	unsigned int		cslen;
	int					stat_loc;

	cslen = sizeof(csin);
	while ((config->socket.cmd = accept(config->socket.server_master,
	(struct sockaddr*)&csin, &cslen)))
	{
		pid = 0;
		if ((pid = fork()) < 0)
			ft_error_child("master_waiting_loop", "fork()", FORK_FAIL);
		if (config->socket.cmd > 0 && pid == 0)
			my_fork_master(config);
		else if (config->socket.cmd > 0 && pid)
			wait4(pid, &stat_loc, 0, NULL);
		if (config->socket.cmd < 0)
			printf("Accept() error.\n");
	}
	close(config->socket.server_master);
	return (0);
}
