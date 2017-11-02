/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndudnicz <ndudnicz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/20 10:52:49 by ndudnicz          #+#    #+#             */
/*   Updated: 2017/10/20 10:52:50 by ndudnicz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftasm.h"
#include "config.h"
#include "packet.h"
#include "send_packet.h"

/*
** Display an error message and return the int ret parameter.
** Usage: return (ft_error(bin, filename, ERROR_DEFINE, 1))
*/

int		ft_error(char const *exec_name, char const *filename,
				char const *type, int ret)
{
	ft_putstr_fd(exec_name, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(filename, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(type, 2);
	ft_putstr_fd("\n", 2);
	return (ret);
}

/*
** Display an error message and does nothing.
*/

void	ft_error_child(char const *cmd, char const *filename, char const *type)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(filename, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(type, 2);
	ft_putstr_fd("\n", 2);
}
