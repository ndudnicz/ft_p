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

int		set_bind_ip(t_config *config, char const *exec_name, char const *param)
{
	config->options |= BIND_IP;
	if (!param)
		return (ft_error(exec_name, "-b", BIND_FAILED, 1));
	else if (!(config->ip_str = ft_strdup(param)))
		return (ft_error(exec_name, "", MALLOC_FAIL, 1));
	else
		return (0);
}
