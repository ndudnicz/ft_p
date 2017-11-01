/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_data_connection.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndudnicz <ndudnicz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 18:00:43 by ndudnicz          #+#    #+#             */
/*   Updated: 2017/11/01 18:00:44 by ndudnicz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPEN_DATA_CONNECTION_H
# define OPEN_DATA_CONNECTION_H

int		open_data_connection(t_config *config, t_packet *packet,
					int (*transfert)(t_config*, char const*));

#endif
