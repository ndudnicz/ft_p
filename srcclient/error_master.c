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

#include "error_master.h"
#include "libftasm.h"

/*
** Display an error message and return the int ret parameter.
** Usage: return (ft_error(bin, filename, ERROR_DEFINE, 1))
*/

int	ft_error(char const *exec_name, char const *filename,
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
