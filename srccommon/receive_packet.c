/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive_packet.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndudnicz <ndudnicz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 17:43:55 by ndudnicz          #+#    #+#             */
/*   Updated: 2017/11/01 17:43:59 by ndudnicz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/socket.h>

#include "config.h"
#include "packet.h"
#include "libftasm.h"
#include "error.h"
#include "libft.h"
#include "receive_packet.h"

static int	print_ls(t_config *config, t_packet *packet, int ret)
{
	((char*)packet)[ret] = 0;
	ret = ft_putstr((char*)packet);
	// ft_putendl("\nss");
	// ft_putnbr_endl(ret);
	// if (ret == HEADER_SIZE && ((char*)packet)[ret - 1] > 10)
	// {
		// while ((ret = read(config->socket.cmd, config->buf, MAX_PACKET_SIZE - 1)) > 0)
		while ((ret = recv(config->socket.cmd, config->buf, MAX_PACKET_SIZE - 1, 0)) >= 0)
		{
			config->buf[ret] = 0;
			ft_putstr(config->buf);
			// ft_putnbr_endl(ret);
			// if (!ret)
			// 	return (0);
			// else
			// 	return (receive_packet(config, config->socket.cmd, packet, ST_LS));
			if (ret < MAX_PACKET_SIZE - 1)
				break ;
		}
	// }
	return (0);
}

int			read_timeout(t_config *config, int socket, unsigned short read_size)
{
	int		ret;
	int		timeout;

	timeout = 0;
	// ft_bzero(config->buf, MAX_PACKET_SIZE);
	// while ((ret = read(socket, config->buf, read_size)) == 0)
	while ((ret = recv(socket, config->buf, read_size, 0)) == 0)
	{
		if (timeout > 100)
			return (-1);
		ret = read(socket, config->buf, read_size);
		// ft_putstr("read 0 ");
		// ft_putnbr_endl(timeout);
		timeout++;
	}
	return (ret);
}

int			receive_packet(t_config *config, int socket, t_packet *packet,
							unsigned short cmd)
{
	int			ret1;
	int			ret2;
	t_packet	*tmp;

	ret2 = 0;
	ft_bzero(config->buf, MAX_PACKET_SIZE);
	ft_bzero((char*)packet, MAX_PACKET_SIZE);
	if (cmd == ST_LS)
		return (print_ls(config, packet, 0));
	else
	{
		ret1 = read_timeout(config, socket, HEADER_SIZE);
		tmp = (t_packet*)config->buf;
		if (ret1 > 0)
			ft_memcpy((char*)packet, tmp, ret1);
		if (ret1 == HEADER_SIZE && (tmp->magic == CIGAM || tmp->magic == MAGIC) &&
		ntohs(tmp->size) <= MAX_PACKET_SIZE)
		{
			if ((ret2 = read(socket, config->buf, ntohs(tmp->size))) < 0)
			// if ((ret2 = read_timeout(config, socket, ntohs(tmp->size))) < 0)
				return (ft_error("receive_cmd_packet", "read()", READ_FAIL, -1));
			config->buf[ret2] = 0;
			ft_memcpy((char*)packet + ret1, config->buf, ret2);
			unforge_packet(packet);
		}
		return (ret1 + ret2);
	}
}
