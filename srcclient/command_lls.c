/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_lls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndudnicz <ndudnicz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 17:42:11 by ndudnicz          #+#    #+#             */
/*   Updated: 2017/11/01 17:42:12 by ndudnicz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "config.h"
#include "libftasm.h"

void	lls(char const *arg)
{
	if (ft_strlen(arg))
		execl(LS_PATH, LS_PATH, arg, ".", NULL);
	else
		execl(LS_PATH, LS_PATH, "-pa", ".", NULL);
}
