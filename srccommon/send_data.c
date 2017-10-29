#include <fcntl.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/socket.h>

#include "config.h"
#include "error.h"
#include "packet.h"
#include "send_packet.h"
#include "debug.h"//
#include "libft.h"//
#include "receive_packet.h"

static int	ping_pong(t_config *config, t_packet *packet_ping,
	t_packet *packet_pong)
{
	int		i;

	i = 0;
	ft_putendl("PING");
	send_packet(config->socket.data, packet_ping);
	receive_packet(config, config->socket.data, packet_pong);
	while (i < 100 && packet_pong->type != T_PING_PONG)
	{
		i++;
		ft_putendl("PING");
		send_packet(config->socket.data, packet_ping);
		receive_packet(config, config->socket.data, packet_pong);
	}
	return (i);
}

static int	chunk_data(t_config *config, char *data, int const chunks_number,
						unsigned long int const file_size)
{
	int				i;
	t_packet		*packet_ping;
	t_packet		*packet_pong;
	unsigned int	size;

	if (!(packet_ping = (t_packet*)malloc(sizeof(t_packet))) ||
	!(packet_pong = (t_packet*)malloc(sizeof(t_packet))))
		return (ft_error("Error", "send_data", MALLOC_FAIL, 1));
	i = 0;
	while (i < chunks_number)
	{
		if (i == chunks_number - 1)
			size = HEADER_SIZE + (file_size - (i * MAX_DATA_SIZE));
		else
			size = MAX_PACKET_SIZE;
		forge_packet(packet_ping, ((size << 16) + T_DATA)
		,&data[i * MAX_DATA_SIZE], chunks_number);
		if (ping_pong(config, packet_ping, packet_pong) > 99)
			return (ft_error("Error", "send_data", MALLOC_FAIL, 1));
		i++;
	}
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
