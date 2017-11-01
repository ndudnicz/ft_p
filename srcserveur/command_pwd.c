/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndudnicz <ndudnicz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 17:44:44 by ndudnicz          #+#    #+#             */
/*   Updated: 2017/11/01 17:44:49 by ndudnicz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "libftasm.h"
#include "config.h"
#include "packet.h"
#include "send_message.h"
#include "error.h"
#include "my_syslimits.h"

/*
** Get the current working directory and send it to the client
*/

void	pwd(t_config *config)
{
	char	pwd[PATH_MAX];

	if (getcwd(pwd, PATH_MAX))
		send_message(config, pwd, "Server");
	else
		send_message(config, INTERNAL_ERROR, "Server");
	exit(0);
}
