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

static int	print_ls(t_config *config, int ret)
{
	config->buf[ret] = 0;
	ret = ft_putstr(config->buf);
	if (ret < HEADER_SIZE)
		return (0);
	while ((ret = recv(config->socket.cmd, config->buf, MAX_PACKET_SIZE - 1, 0))
	> 0)
	{
		config->buf[ret] = 0;
		ft_putstr(config->buf);
		if (ret < MAX_PACKET_SIZE - 1)
			break ;
	}
	return (0);
}

static int	read_timeout(t_config *config, int socket, unsigned short read_size)
{
	int		ret;
	int		timeout;

	timeout = 0;
	while ((ret = recv(socket, config->buf, read_size, 0)) == 0)
	{
		if (timeout > 10000)
			return (-1);
		timeout++;
	}
	return (ret);
}

static void	double_bzero(char *p1, size_t const s1, char *p2, size_t const s2)
{
	ft_bzero(p1, s1);
	ft_bzero(p2, s2);
}

int			receive_packet(t_config *config, int socket, t_packet *packet,
							unsigned short cmd)
{
	int			ret1;
	int			ret2;
	t_packet	*tmp;

	ret2 = 0;
	double_bzero(config->buf, MAX_PACKET_SIZE, (char*)packet, MAX_PACKET_SIZE);
	ret1 = read_timeout(config, socket, HEADER_SIZE);
	if (ret1 > 0 && cmd == ST_LS)
		return (print_ls(config, ret1));
	else
	{
		tmp = (t_packet*)config->buf;
		if (ret1 > 0)
			ft_memcpy((char*)packet, tmp, ret1);
		if (ret1 == HEADER_SIZE && (tmp->magic == CIGAM || tmp->magic == MAGIC)
		&& ntohs(tmp->size) <= MAX_PACKET_SIZE)
		{
			if ((ret2 = recv(socket, config->buf, ntohs(tmp->size), 0)) < 0)
				return (ft_error("receive_packet()", "recv()", READ_FAIL, -1));
			config->buf[ret2] = 0;
			ft_memcpy((char*)packet + ret1, config->buf, ret2);
			unforge_packet(packet);
		}
		return (ret1 + ret2);
	}
}
