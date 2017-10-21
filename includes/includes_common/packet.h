#ifndef PACKET_H
# define PACKET_H

/*
** Define the packet sizes.
*/

# define SIZE_BYTE_SIZE		(sizeof(unsigned short))
# define TYPE_BYTE_SIZE		(sizeof(unsigned short))
# define HEADER_SIZE		(SIZE_BYTE_SIZE + TYPE_BYTE_SIZE)
# define MAX_PACKET_SIZE	65536
# define MAX_DATA_SIZE		(MAX_PACKET_SIZE - HEADER_SIZE)

/*
** Define how to get type value, exemple: packet->type & (MASK_CMD | LS)
*/

# define MASK_CMD	0x0100
# define LS			0x01
# define CD			0x02
# define GET		0x04
# define PUT		0x08
# define PWD		0x10
# define LLS		0x20
# define LCD		0x40
# define LPWD		0x80

# define T_MESSAGE	0x0001

typedef struct	s_packet
{
	unsigned short	size;
	unsigned short	type;
	char			data[MAX_DATA_SIZE];
}				t_packet;

void	forge_packet(unsigned short const size,
					unsigned short const type,
					char const* data,
					t_packet *packet);

void	unforge_packet(t_packet *packet);

#endif
