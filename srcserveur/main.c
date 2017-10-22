#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <arpa/inet.h>
#include "packet.h"
#include "libftasm.h"
#include "packet.h"
#include "switch_packet_type.h"
#include "config.h"
#include "error_master.h"
#include "options_handling.h"
#include "open_connection.h"
#include "debug.h"//
#include "waiting_loop.h"

/*
** Display a usefull usage message.
*/

int		usage(char const *bin)
{
	printf("Usage: %s <port>\n", bin);
	return (1);
}

/*
** The beginning of everything.
*/

// int		create_server(int port)
// {
// 	int					sock;
// 	struct protoent		*proto;
// 	struct sockaddr_in	sin;
//
// 	proto = getprotobyname("tcp");
// 	if (proto == 0)
// 	{
// 		return (-1);
// 	}
// 	sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
// 	sin.sin_family = AF_INET;
// 	sin.sin_port = htons(port);
// 	sin.sin_addr.s_addr = htonl(INADDR_ANY);
// 	bind(sock, (const struct sockaddr*)&sin, sizeof(sin));
// 	listen(sock, 1);
// 	return (sock);
// }
int		main(int ac, char **av)
{
	/*
	int					sock;
	int					port;
	struct sockaddr_in	csin;
	unsigned int		cslen;
	char				buf[MAX_PACKET_SIZE] = {0};
	int					r;
	t_packet			*packet;
	int					pid;

	pid = 0;
	if (ac != 2)
		return (usage(av[0]));
	port = ft_atoi(av[1]);
	sock = create_server(port);
	cs = accept(sock, (struct sockaddr*)&csin, &cslen);
	while ((r = read(cs, buf, MAX_PACKET_SIZE)) > 0)
	{
		packet = (t_packet*)buf;
		print_packet(packet, 1);
		pid = fork(); // HANDLE FORK ERROR
		if (pid == 0)
			switch_packet_type(cs, packet);
		// else
		// 	ft_putstr("DONE");
		ft_bzero(buf, MAX_PACKET_SIZE);
	}
	close(cs);
	close(sock);
	return (0);
	*/
	t_config	*config;

	if (ac < 2)
	{
		return (usage(av[0]));
	}
	else if (!(config = (t_config*)malloc(sizeof(t_config))))
	{
		return (ft_error(av[0], "", MALLOC_FAIL, 1));
	}
	else
	{
		if (get_options(config, &ac, av) > 0)
			return (1);
		else if (open_connection(config, av[1]) > 0)
			return (1);
		else if (master_waiting_loop(config) > 0)
			return (1);
		else
			return (0);
	}
	return (0);
}
