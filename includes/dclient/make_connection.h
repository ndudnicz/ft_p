/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_connection.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndudnicz <ndudnicz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 17:59:25 by ndudnicz          #+#    #+#             */
/*   Updated: 2017/11/01 17:59:27 by ndudnicz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAKE_CONNECTION_H
# define MAKE_CONNECTION_H

# include "config.h"

int		make_connection(t_config *config, char const *ip_str,
								char const *cmd_port_str);
int		make_data_connection(t_config *config, char const *filename,
								int (*transfert)(t_config*, char const*, int));

#endif
