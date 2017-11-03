/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_lpwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndudnicz <ndudnicz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 17:42:16 by ndudnicz          #+#    #+#             */
/*   Updated: 2017/11/01 17:42:17 by ndudnicz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

#include "config.h"
#include "packet.h"
#include "error.h"
#include "my_syslimits.h"

/*
** Get the current working directory and display it on stdout
*/

int		lpwd(void)
{
	char	pwd[PATH_MAX];

	if (getcwd(pwd, PATH_MAX))
		printf("%s\n", pwd);
	else
		ft_error_child("LPWD", INTERNAL_ERROR, "FILE PERMISSION ?");
	return (0);
}
