#ifndef PACKET_H
# define PACKET_H

/*
** Magic number
*/

# define MAGIC	0xaefcaeba

/*
** Define the packet sizes.
*/

# define MAGIC_SIZE			(sizeof(unsigned int))
# define CHUNK_N_SIZE		(sizeof(unsigned long int))
# define SIZE_SIZE			(sizeof(unsigned short))
# define TYPE_SIZE			(sizeof(unsigned short))
# define HEADER_SIZE		(MAGIC_SIZE + SIZE_SIZE + TYPE_SIZE + CHUNK_N_SIZE)
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
** T_SPEC_TYPE
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
	unsigned long	chunks_number;
	unsigned short	size;
	unsigned short	type;
	char			data[MAX_DATA_SIZE];
}				t_packet;

void				forge_packet(t_packet *packet, unsigned int size_type,
								char const* data, unsigned long int st_size);

void				unforge_packet(t_packet *packet);

unsigned long int	get_chunk_number(unsigned long int st_size);


#endif
