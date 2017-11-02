/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndudnicz <ndudnicz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 17:43:50 by ndudnicz          #+#    #+#             */
/*   Updated: 2017/11/01 17:43:51 by ndudnicz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>

#include "config.h"
#include "packet.h"
#include "libft.h"
#include "libftasm.h"
#include "send_packet.h"
#include "error.h"
#include "receive_packet.h"

static int		ret_error(t_config *config)
{
	ft_putendl("Open() error");
	close(config->socket.data);
	return (1);
}

static int		write_forge_and_send_pong(t_config *config,
										t_packet *packet_pong,
										t_packet *packet_ping,
										int const fd)
{
	t_size_type		size_type;

	write(fd, packet_ping->data, packet_ping->size - HEADER_SIZE);
	size_type.size = HEADER_SIZE + 1;
	size_type.type = T_PING_PONG;
	forge_packet(packet_pong, &size_type, " ", 1);
	send_packet(config->socket.data, packet_pong);
	return (0);
}

static void		close_and_free(int const fd, t_packet **p)
{
	close(fd);
	free(p[0]);
	free(p[1]);
	free(p);
}

static t_packet	**create_packets(void)
{
	t_packet	**double_packet;

	if (!(double_packet = (t_packet**)malloc(sizeof(t_packet*) * 2)))
		return (NULL);
	else if (!(double_packet[0] = (t_packet*)malloc(sizeof(t_packet))))
		return (NULL);
	else if (!(double_packet[1] = (t_packet*)malloc(sizeof(t_packet))))
		return (NULL);
	else
		return (double_packet);
}

int				receive_data(t_config *config, char const *filename, int i)
{
	t_packet	**packets;
	int			fd;
	int			n;
	int			ret;

	n = -1;
	if (!(packets = create_packets()))
		return (ft_error("ERROR", "receive_data", MALLOC_FAIL, 1));
	if ((fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0600)) < 0)
		return (ret_error(config));
	ft_bzero(config->buf, MAX_PACKET_SIZE);
	while (i != n && (ret = receive_packet(config, config->socket.data,
	packets[0], 0)) > 0)
	{
		if (ret <= 0)
			break ;
		if (packets[0]->magic == MAGIC && packets[0]->type == T_DATA)
		{
			n = packets[0]->chunks_number;
			write_forge_and_send_pong(config, packets[1], packets[0], fd);
			i++;
		}
		else if (packets[0]->magic == MAGIC && packets[0]->type == T_CLOSE)
	 		return ft_error("ERROR", "make_data_connection()", CLOSE, 1);
	}
	close_and_free(fd, packets);
	return (0);
}
