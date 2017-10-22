#include "packet.h"
#include <stdio.h>
#include <arpa/inet.h>
#include "libft.h"

void print_packet(t_packet *packet, int print_data)
{
	printf("magic:%x\n", packet->magic);
	printf("chunks number:%lu\n", packet->chunks_number);
	printf("size:%hd\n", packet->size);
	printf("type:%04hx\n", packet->type);
	if (print_data)
		printf("%s\n", packet->data);
}

void print_forged_packet(t_packet *packet, int print_data)
{
	printf("magic:%x\n", ntohl(packet->magic));
	unsigned long int left = ntohl(packet->chunks_number >> 32);
	int right = ntohl((int)packet->chunks_number);
	printf("chunks number:%lu\n", (left << 32) + (unsigned long)right);
	printf("size:%hd\n", ntohs(packet->size));
	printf("type:%04hx\n", ntohs(packet->type));
	if (print_data)
		printf("%s\n", packet->data);
}

void print_command_type(t_packet *packet)
{
	switch (packet->type) {
		case T_MASK_CMD | ST_LS :
			ft_putendl("LS");
			break;
		case T_MASK_CMD | ST_CD :
			ft_putendl("CD");
			break;
		case T_MASK_CMD | ST_GET :
			ft_putendl("GET");
			break;
		case T_MASK_CMD | ST_PUT :
			ft_putendl("PUT");
			break;
		case T_MASK_CMD | ST_PWD :
			ft_putendl("PWD");
			break;
		case T_MASK_CMD | ST_LLS :
			ft_putendl("LLS");
			break;
		case T_MASK_CMD | ST_LCD :
			ft_putendl("LCD");
			break;
		case T_MASK_CMD | ST_LPWD :
			ft_putendl("PWD");
			break;
		default:
			ft_putendl("UNKNOWN COMMAND");
			break;
	}
}
