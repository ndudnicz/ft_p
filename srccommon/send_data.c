#include <fcntl.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <stdio.h>

#include "config.h"
#include "error.h"
#include "packet.h"
#include "send_packet.h"
#include "debug.h"//
#include "libft.h"//
#include "libftasm.h"//
#include "receive_packet.h"

static unsigned int	swap32(unsigned int const n)
{
	return (n << 24 |
		((n << 8) & 0x00ff0000) |
		((n >> 8) & 0x0000ff00) |
		n >> 24);
}

static int	ping_pong(t_config *config, t_packet *packet_ping,
	t_packet *packet_pong)
{
	int		i;

	i = 0;
	send_packet(config->socket.data, packet_ping);
	while (i < 1000 && packet_pong->type != T_PING_PONG)
	{
		i++;
		receive_packet(config, config->socket.data, packet_pong, 0);
	}
	return (i);
}

static int	chunk_data(t_config *config, char *data, int const chunks_number,
						unsigned long int const file_size)
{
	int				i;
	t_packet		*packet_ping;
	t_packet		*packet_pong;
	t_size_type		size_type;


	if (!(packet_ping = (t_packet*)malloc(sizeof(t_packet))) ||
	!(packet_pong = (t_packet*)malloc(sizeof(t_packet))))
		return (ft_error("Error", "send_data", MALLOC_FAIL, 1));
	i = 0;
	size_type.type = T_DATA;
	while (i <= chunks_number)
	{
		ft_bzero((char*)packet_pong, sizeof(t_packet));
		if (i + 1 == chunks_number)
			size_type.size = HEADER_SIZE + file_size % MAX_DATA_SIZE;
		else
			size_type.size = MAX_PACKET_SIZE;
		forge_packet(packet_ping, &size_type ,&data[i * MAX_DATA_SIZE], chunks_number);
		if (!(config->options & IAMSERVER))
			printf("%d / %d\n", i + 1, swap32(packet_ping->chunks_number));
		if (ping_pong(config, packet_ping, packet_pong) >= 100)
			ft_error_child("ERROR", "DATA TRANSFERT", "CONNECTION LOST");
		i++;
	}
	my_free(51,packet_ping);
	my_free(52,packet_pong);
	return (0);
}

int			send_data(t_config *config, char const *filename)
{
	int const		fd = open(filename, O_RDONLY);
	struct stat		stat;
	int				i;
	char			*data;

	if (fd < 0)
		return (ft_error("Error", "send_data", OPEN_FAILED, 1));
	if (fstat(fd, &stat) < 0)
		return (ft_error("Error", "send_data", FSTAT_FAILED, 1));
	if ((data = (char*)mmap(NULL, stat.st_size, PROT_READ, MAP_PRIVATE, fd, 0))
	== MAP_FAILED)
	{
		close(config->socket.data);
		return (ft_error("Error", "send_data", MMAP_FAILED, 1));
	}
	if (chunk_data(config, data, get_chunk_number(stat.st_size),
	stat.st_size) > 0)
	{
		close(config->socket.data);
		return (1);
	}
	close(config->socket.data);
	return (0);
}
