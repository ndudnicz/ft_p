// #include <unistd.h>
#include <stdio.h>//
#include <sys/socket.h>

#include "config.h"
#include "packet.h"
#include "debug.h"//
#include "libft.h"
#include "libftasm.h"
#include "error.h"

static void	print_ls(t_config *config, t_packet *packet)
{
	int		ret;

	if (ft_putstr((char*)packet) > HEADER_SIZE - 1)
	{
		while ((ret =
		read(config->socket.cmd, config->buf, MAX_PACKET_SIZE - 1)) > 0)
		{
			config->buf[ret] = 0;
			ft_putstr(config->buf);
			if (ret < MAX_PACKET_SIZE - 1)
				break ;
		}
	}

}

int		receive_packet(t_config *config, int socket, t_packet *packet,
						unsigned short cmd)
{
	int			ret1;
	int			ret2;
	t_packet	*tmp;

	// ft_putendl("receive_packet <----");
	ft_bzero(config->buf, MAX_PACKET_SIZE);
	while (config->buf[0] == 0)
		ret1 = read(socket, config->buf, HEADER_SIZE);
	// ret1 = recv(socket, config->buf, HEADER_SIZE, 0);
	tmp = (t_packet*)config->buf;
	ft_memcpy((char*)packet, tmp, ret1);
	if (ret1 >= HEADER_SIZE && (tmp->magic == CIGAM || tmp->magic == MAGIC))
	{
		if ((ret2 = read(socket, config->buf, ntohs(tmp->size))) < 0)
		// if ((ret2 = recv(socket, config->buf, ntohs(tmp->size), 0)) < 0)
			ft_error_child("receive_cmd_packet", "read()", READ_FAIL);
		config->buf[ret2] = 0;
		ft_memcpy((char*)packet + ret1, config->buf, ret2);
		unforge_packet(packet);
		// print_packet(packet, 0);
	}
	else if (cmd == ST_LS)
		print_ls(config, packet);
	return (ret1 + ret2);
}
