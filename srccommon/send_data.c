#include <fcntl.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>

#include "config.h"
#include "packet.h"
#include "send_packet.h"
#include "debug.h"
#include "libft.h"//

static int	chunk_data(int const socket, char *data, int const chunks_number,
						unsigned long int const file_size)
{
	int				i;
	t_packet		*packet;
	unsigned int	size;

	if (!(packet = (t_packet*)malloc(sizeof(t_packet))))
		return (1);
	i = 0;
	// ft_putnbr_endl(file_size);
	// int fd = open("toto", O_RDWR | O_CREAT | O_TRUNC, 0600);//
	while (i < chunks_number)
	{
		if (i == chunks_number - 1)
			size = HEADER_SIZE + (file_size - (i * MAX_DATA_SIZE));
		else
			size = MAX_PACKET_SIZE;
		// ft_putnbr_endl(size);
		forge_packet(packet, ((size << 16) | T_DATA), &data[i * MAX_DATA_SIZE], chunks_number);
		send_packet(socket, packet);
		// unforge_packet(packet);
		// write(fd, (void*)packet->data, (unsigned int)packet->size - HEADER_SIZE/*file_size*/);//
		i++;
	}
	// close(fd);//
	// exit(0);
	return (0);
}

int			send_data(t_config *config, char const *filename)
{
	int const		fd = open(filename, O_RDONLY);
	struct stat		stat;
	int				i;
	char			*data;

	if (fd < 0 || fstat(fd, &stat) < 0)
		return (1);
	// ft_putnbr_endl(stat.st_mode);
	if ((data = (char*)mmap(NULL, stat.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		return (1);
	chunk_data(config->socket.data, data, get_chunk_number(stat.st_size), stat.st_size);
	close(config->socket.data);
	return (0);

}
