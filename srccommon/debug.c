/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndudnicz <ndudnicz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 14:57:06 by ndudnicz          #+#    #+#             */
/*   Updated: 2017/10/23 14:57:07 by ndudnicz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <arpa/inet.h>

#include "libft.h"
#include "packet.h"
#include "config.h"
#include "user_input.h"

void	print_packet(t_packet *packet, int print_data)
{
	printf("\n------------------------------------\n");
	printf("magic:%x\n", packet->magic);
	printf("chunks number:%u\n", packet->chunks_number);
	printf("size:%hd\n", packet->size);
	printf("type:%04hx\n", packet->type);
	if (print_data)
		printf("%s\n", packet->data);
	printf("------------------------------------\n\n");
}

static unsigned long int	my_swap64(unsigned long int n)
{
	return ((n & 0x00000000000000ff) << 56 |
		(n & 0x000000000000ff00) << 40 |
		(n & 0x0000000000ff0000) << 24 |
		(n & 0x00000000ff000000) << 8 |
		(n & 0x000000ff00000000) >> 8 |
		(n & 0x0000ff0000000000) >> 24 |
		(n & 0x00ff000000000000) >> 40 |
		(n & 0xff00000000000000) >> 56);
}

void	print_forged_packet(t_packet *packet, int print_data)
{

	if (packet->magic != ntohl(MAGIC))
		packet->chunks_number = my_swap64(packet->chunks_number);

	printf("\n------------------------------------\n");
	printf("magic:%x\n", ntohl(packet->magic));
	printf("chunks number:%u\n", ntohl(packet->chunks_number));
	printf("size:%hd\n", ntohs(packet->size));
	printf("type:%04hx\n", ntohs(packet->type));
	if (print_data)
		printf("%s\n", packet->data);
	printf("------------------------------------\n\n");
}

void	print_command_type(t_packet *packet)
{
	return ;
}

void print_input(t_input *input)
{
	printf("cmd:%04hx\n", input->cmd);
	printf("arg:%s\n", input->arg);
}
