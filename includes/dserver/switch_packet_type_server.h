/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch_packet_type_server.h                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndudnicz <ndudnicz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 18:05:35 by ndudnicz          #+#    #+#             */
/*   Updated: 2017/11/01 18:05:36 by ndudnicz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SWITCH_PACKET_TYPE_SERVER_H
# define SWITCH_PACKET_TYPE_SERVER_H

int		switch_packet_type_server(t_config *config, t_packet *packet);
void	switch_packet_type_server_no_fork(t_config *config, t_packet *packet);

#endif
