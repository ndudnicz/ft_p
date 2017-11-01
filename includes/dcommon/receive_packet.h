/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive_packet.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndudnicz <ndudnicz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 18:01:28 by ndudnicz          #+#    #+#             */
/*   Updated: 2017/11/01 18:01:29 by ndudnicz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RECEIVE_PACKET_H
# define RECEIVE_PACKET_H

int		receive_packet(t_config *config, int const socket, t_packet *packet,
						unsigned short cmd);

#endif
