/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options_handling_tool.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndudnicz <ndudnicz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 10:59:34 by ndudnicz          #+#    #+#             */
/*   Updated: 2017/11/02 10:59:36 by ndudnicz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "libftasm.h"
#include "config.h"
#include "my_limits.h"
#include "error.h"

int		set_root_folder(t_config *config, char const *exec_name,
						char const *param)
{
	config->options |= ROOT_FOLDER;
	if (chdir(param) < 0)
		return (ft_error(exec_name, "-f", CHDIR_FAILED, 1));
	else
		return (0);
}

int		valid_port_string(char const *port)
{
	int		i;

	i = 0;
	if (ft_strlen(port) > 5)
		return (ft_error("ERROR", "PORT", BAD_PORT, 1));
	while (port && port[i])
	{
		if (ft_isdigit((int)port[i]))
			i++;
		else
			return (ft_error("ERROR", "", BAD_PORT, 1));
	}
	if (ft_atoi(port) > USHORTMAX)
		return (ft_error("ERROR", "PORT", BAD_PORT, 1));
	else
		return (0);
}
