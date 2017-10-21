#include <stdio.h>
#include <stdlib.h>
#include "packet.h"
#include "libftasm.h"
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include "packet.h"

int		usage(char const *bin)
{
	printf("Usage: %s <port>\n", bin);
	return (1);
}

int		create_server(int port)
{
	int					sock;
	struct protoent		*proto;
	struct sockaddr_in	sin;

	proto = getprotobyname("tcp");
	if (proto == 0)
	{
		return (-1);
	}
	sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	bind(sock, (const struct sockaddr*)&sin, sizeof(sin));
	listen(sock, 1);
	return (sock);
}
#include "debug.h"
int		main(int ac, char **av)
{
	int					sock;
	int					port;
	int					cs;
	struct sockaddr_in	csin;
	unsigned int		cslen;
	char				buf[MAX_PACKET_SIZE] = {0};
	int					r;
	t_packet			*packet;

	if (ac != 2)
		return (usage(av[0]));
	port = ft_atoi(av[1]);
	sock = create_server(port);
	cs = accept(sock, (struct sockaddr*)&csin, &cslen);
	while ((r = read(cs, buf, MAX_PACKET_SIZE)) > 0)
	{
		packet = (t_packet*)buf;
		unforge_packet(packet);
		if (packet->type & T_MESSAGE && !(packet->type & MASK_CMD))
			print_packet(packet, 1);
		else
			ft_putstr("DONE");
		ft_bzero(buf, MAX_PACKET_SIZE);
	}

	close(cs);
	close(sock);
	return (0);
}
