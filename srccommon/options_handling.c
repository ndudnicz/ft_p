/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options_handling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndudnicz <ndudnicz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/02 11:12:29 by ndudnicz          #+#    #+#             */
/*   Updated: 2017/11/01 17:43:37 by ndudnicz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"
#include "libft.h"
#include "error.h"
#include "my_limits.h"
#include "libftasm.h"
#include "my_syslimits.h"
#include "options_handling.h"

/*
** Moves NULLs argv to the end of the array. Options are set in config
** and doesn't exist anymore in argv.
*/

static void	del_null_params(int *ac, char **av, int offset)
{
	int		i;
	int		n;
	char	*tmp;

	n = 1;
	while (n < *ac)
	{
		i = 1;
		while (i < *ac - 1)
		{
			if (av[i] == NULL)
			{
				tmp = av[i];
				av[i] = av[i + 1];
				av[i + 1] = tmp;
			}
			i++;
		}
		n++;
	}
	*ac -= offset;
}

static int	switch_set_options(char const *exec_name, char const *arg,
								char const *param, t_config *config)
{
	if (!arg)
		return (0);
	else
		arg++;
	while (arg && *arg)
	{
		if (*arg && ft_strchr(PARAMS_STR, (int)(*arg)))
		{
			if (*arg == ROOT_FOLDER_CHAR && !*(arg + 1))
				return (set_root_folder(config, exec_name, param));
			else
				return (ft_error(exec_name, "", UNKNOW_ARG, 1));
		}
		else
			return (ft_error(exec_name, "", UNKNOW_ARG, 1));
		arg++;
	}
	return (0);
}

/*
** Check the port_str
** Return 0 if port number is valid
** Display an error message and return 1 if the port number is not valid
** Invalid: port > SHORTMAX || port < 0 || non digit char
*/

static int	valid_port_number(char const *exec_name, int *ac, char **av)
{
	int		i;
	char	*port_str;

	if (*ac == 2 || *ac == 3)
		port_str = av[*ac - 1];
	else
		return (ft_error(exec_name, "", BAD_PORT, 1));
	i = 0;
	if (valid_port_string(port_str) > 0)
		return (1);
	else
		return (0);
	// if (ft_strlen(port_str) > 5)
	// 	return (ft_error(exec_name, "", BAD_PORT, 1));
	// while (port_str && port_str[i])
	// {
	// 	if (ft_isdigit((int)port_str[i]))
	// 		i++;
	// 	else
	// 		return (ft_error(exec_name, "", BAD_PORT, 1));
	// }
	// if (ft_atoi(port_str) > USHORTMAX)
	// 	return (ft_error(exec_name, "", BAD_PORT, 1));
}

/*
** Get and set the current working directory in *config
*/

static int	set_root(t_config *config)
{
	if (getcwd(config->root, PATH_MAX))
		return (0);
	else
		return (ft_error("options_handling", "set_root()", GETCWD_FAILED, 1));
}

/*
** Parse argv and set argv[index] at NULL if an options was found.
*/

int			get_options(t_config *config, int *ac, char **av)
{
	int		i;
	int		n;

	i = 1;
	n = 0;
	while (i < *ac)
	{
		if (av[i][0] == '-')
		{
			if (switch_set_options(av[0], av[i], av[i + 1], config) > 0)
				return (1);
			av[i] = NULL;
			av[i + 1] = NULL;
			n += 2;
			i += 2;
		}
		else
			i++;
	}
	del_null_params(ac, av, n);
	if (valid_port_number(av[0], ac, av) > 0 || set_root(config) > 0)
		return (1);
	config->ip_str = config->ip_str ? config->ip_str :
	ft_strdup(DEFAULT_IP_BIND);
	return (0);
}
