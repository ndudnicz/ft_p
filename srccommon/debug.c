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

#include <stdlib.h>

#include "libft.h"
#include "config.h"

#include "config.h"
#include "packet.h"
#include "user_input.h"

#include <stdio.h>
void	print_packet(t_packet *packet, int print_data)
{
	printf("\n------------------------------------\n");
	printf("magic:%x\n", packet->magic);
	printf("chunks number:%u\n", packet->chunks_number);
	printf("size:%hu\n", packet->size);
	printf("type:%04hx\n", packet->type);
	if (print_data)
		printf("%s\n", packet->data);
	printf("------------------------------------\n\n");
}

void	print_forged_packet(t_packet *packet, int print_data)
{


	printf("\n------------------------------------\n");
	printf("magic:%x\n", ntohl(packet->magic));
	printf("chunks number:%u\n", ntohs(packet->chunks_number));
	printf("size:%hu\n", ntohs(packet->size));
	printf("type:%04hx\n", ntohs(packet->type));
	if (print_data)
		printf("%s\n", packet->data);
	printf("------------------------------------\n\n");
}
/*
void print_input(t_input *input)
{
	printf("cmd:%04hx\n", input->cmd);
	printf("arg:%s\n", input->arg);
}
*/

void	my_free(int n, void *ptr, unsigned char const options)
{
	unsigned char	p = options;
	p = 0;
	// if (options & DEBUG)
		ft_putnbr_endl(n);
	free(ptr);
}
