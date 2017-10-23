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
	printf("chunks number:%lu\n", packet->chunks_number);
	printf("size:%hd\n", packet->size);
	printf("type:%04hx\n", packet->type);
	if (print_data)
		printf("%s\n", packet->data);
	printf("------------------------------------\n\n");
}

void	print_forged_packet(t_packet *packet, int print_data)
{
	unsigned long int const		left = ntohl(packet->chunks_number >> 32);
	int const					right = ntohl((int)packet->chunks_number);

	printf("\n------------------------------------\n");
	printf("magic:%x\n", ntohl(packet->magic));
	printf("chunks number:%lu\n", (left << 32) + (unsigned long)right);
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
	printf("cmd:%hhx\n", input->cmd);
	printf("arg:%s\n", input->arg);
}
