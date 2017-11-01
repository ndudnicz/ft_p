/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndudnicz <ndudnicz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 18:00:13 by ndudnicz          #+#    #+#             */
/*   Updated: 2017/11/01 18:00:14 by ndudnicz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

# include "user_input.h"

void	print_packet(t_packet *packet, int print_data);
void	print_forged_packet(t_packet *packet, int print_data);
void	print_input(t_input *input);
void	my_free(int n, void *ptr);

#endif
