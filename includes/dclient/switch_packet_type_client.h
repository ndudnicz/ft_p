/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch_packet_type_client.h                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndudnicz <ndudnicz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 17:59:34 by ndudnicz          #+#    #+#             */
/*   Updated: 2017/11/01 17:59:37 by ndudnicz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SWITCH_PACKET_TYPE_CLIENT_H
# define SWITCH_PACKET_TYPE_CLIENT_H

int		switch_packet_type_client(t_config *config, t_packet *packet,
									char const *arg);

#endif
