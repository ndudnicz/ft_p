#include "packet.h"
#include <stdio.h>
#include <arpa/inet.h>

void print_packet(t_packet *packet, int print_data)
{
	printf("size:%hd\n", packet->size);
	printf("type:%hd\n", packet->type);
	if (print_data)
		printf("%s\n", packet->data);
}

void print_forged_packet(t_packet *packet, int print_data)
{
	printf("size:%hd\n", ntohs(packet->size));
	printf("type:%hd\n", ntohs(packet->type));
	if (print_data)
		printf("%s\n", packet->data);
}
