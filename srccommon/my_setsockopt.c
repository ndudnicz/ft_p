/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_setsockopt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndudnicz <ndudnicz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 10:20:32 by ndudnicz          #+#    #+#             */
/*   Updated: 2017/11/18 10:20:33 by ndudnicz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/socket.h>
#include <stdlib.h>

#include "config.h"
#include "error.h"

int		my_setsockopt(int socket)
{
	struct timeval	timeout;
	int				enable;

	enable = 1;
	timeout.tv_sec = 10;
	timeout.tv_usec = 0;
	if (setsockopt(socket, SOL_SOCKET, SO_RCVTIMEO, &timeout,
	sizeof(timeout)) < 0)
		return (ft_error("ERROR", "my_setsockopt()", SETSOCKOPT, 1));
	else if (setsockopt(socket, SOL_SOCKET, SO_REUSEADDR, &enable,
	sizeof(enable)) < 0)
		return (ft_error("ERROR", "my_setsockopt()", SETSOCKOPT, 1));
	else
		return (0);
}
