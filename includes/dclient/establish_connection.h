/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   establish_connection.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndudnicz <ndudnicz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 17:59:25 by ndudnicz          #+#    #+#             */
/*   Updated: 2017/11/01 17:59:27 by ndudnicz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ESTABLISH_CONNECTION_H
# define ESTABLISH_CONNECTION_H

# include "config.h"

int		establish_connection(t_config *config, char const *ip_str,
								char const *cmd_port_str);
int		establish_data_connection(t_config *config, char const *filename,
								int (*transfert)(t_config*, char const*));

#endif
