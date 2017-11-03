/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   packet.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndudnicz <ndudnicz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 11:41:21 by ndudnicz          #+#    #+#             */
/*   Updated: 2017/10/25 11:41:22 by ndudnicz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PACKET_H
# define PACKET_H

/*
** Magic number
*/

# define MAGIC	0xaefcaeba
# define CIGAM	0xbaaefcae

/*
** Define the packet sizes.
*/

# define MAGIC_SIZE			(sizeof(unsigned int))
# define CHUNK_N_SIZE		(sizeof(unsigned int))
# define SIZE_SIZE			(sizeof(unsigned short))
# define TYPE_SIZE			(sizeof(unsigned short))
# define HEADER_SIZE_NORME	(MAGIC_SIZE + SIZE_SIZE + TYPE_SIZE + CHUNK_N_SIZE)
# define HEADER_SIZE		(unsigned short)HEADER_SIZE_NORME
# define MAX_PACKET_SIZE	0x1000
# define MAX_DATA_SIZE		(MAX_PACKET_SIZE - HEADER_SIZE)

/*
** Generic types
*/
# define T_MESSAGE				0x1ff1
# define T_DATA					0x2ff2
# define T_PING_PONG			0x4ff4
# define T_CLOSE				0x8ff8

/*
** T_SPEC_TYPE
*/
# define T_MASK_CMD			0x01ff
# define T_MASK_DATA		0x3fff

/*
** T_DATA subtypes
*/
# define ASK_NEW_DATA_CONNECTION	0x1000
# define SEND_NEW_DATA_CONNECTION	0x2000

/*
** T_MASK_CMD subtypes
*/
# define ST_MASK		0x0fff
# define ST_CMD_LOCAL	0x0001
# define ST_LS			0x0100
# define ST_CD			0x0102
# define ST_GET			(0x0104 | ASK_NEW_DATA_CONNECTION)
# define ST_PUT			(0x0108 | ASK_NEW_DATA_CONNECTION)
# define ST_PWD			0x0110
# define ST_LLS			(0x0120 | ST_CMD_LOCAL)
# define ST_LCD			(0x0140 | ST_CMD_LOCAL)
# define ST_LPWD		(0x0180 | ST_CMD_LOCAL)
# define ST_QUIT		0xffff

typedef struct		s_packet
{
	unsigned int	magic;
	unsigned int	chunks_number;
	unsigned short	size;
	unsigned short	type;
	char			data[MAX_DATA_SIZE];
}					t_packet;

typedef struct		s_size_type
{
	unsigned short	size;
	unsigned short	type;
}					t_size_type;

void				forge_packet(t_packet *packet, t_size_type const *size_type,
								char const *data, unsigned int chunks);
void				unforge_packet(t_packet *packet);
unsigned int		get_chunk_number(unsigned long int st_size);

#endif
