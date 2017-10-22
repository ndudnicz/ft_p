#ifndef PACKET_H
# define PACKET_H

/*
** Magic number
*/

# define MAGIC	0xaefcaeba

/*
** Define the packet sizes.
*/

# define MAGIC_BYTE_SIZE	(sizeof(unsigned int))
# define SIZE_BYTE_SIZE		(sizeof(unsigned short))
# define TYPE_BYTE_SIZE		(sizeof(unsigned short))
# define HEADER_SIZE		(MAGIC_BYTE_SIZE + SIZE_BYTE_SIZE + TYPE_BYTE_SIZE)
# define MAX_PACKET_SIZE	65536
# define MAX_DATA_SIZE		(MAX_PACKET_SIZE - HEADER_SIZE)

/*
** Packet type is defined as follow:
** (T_GENERIC_TYPE) || (T_SPEC_TYPE | T_SPEC_SUBTYPE)
*/

/*
** Generic types
*/

# define T_MESSAGE	0x0001

/*
** Spec types
*/

# define T_MASK_CMD	0x0100

/*
** T_MASK_CMD subtypes
*/

# define ST_LS		0x0001
# define ST_CD		0x0002
# define ST_GET		0x0004
# define ST_PUT		0x0008
# define ST_PWD		0x0010
# define ST_LLS		0x0020
# define ST_LCD		0x0040
# define ST_LPWD	0x0080


typedef struct	s_packet
{
	unsigned int	magic;
	unsigned short	size;
	unsigned short	type;
	char			data[MAX_DATA_SIZE];
}				t_packet;

void	forge_packet(unsigned short const size, unsigned short const type,
					char const* data, t_packet *packet);

void	unforge_packet(t_packet *packet);

#endif
