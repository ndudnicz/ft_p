/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options_handling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndudnicz <ndudnicz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/02 11:12:29 by ndudnicz          #+#    #+#             */
/*   Updated: 2017/09/02 11:12:30 by ndudnicz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"
#include "libft.h"
#include "error_master.h"
#include "libftasm.h"

static void	del_null_params(int const ac, char **av)
{
	int		i;
	int		n;
	char	*tmp;

	n = 1;
	while (n < ac)
	{
		i = 1;
		while (i < ac - 1)
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
}

static int	set_options(char *arg, t_config *config)
{
	arg += arg ? 1 : 0;
	while (arg && *arg)
	{
		if (*arg && ft_strchr(PARAMS_STR, (int)(*arg)))
		{
			// config->options |= *arg == SORT_NUM_CHAR ? SORT_NUM : 0x00;
		}
		else
			return (1);
		arg++;
	}
	return (0);
}

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
			if (set_options(av[i], config) > 0)
				return (ft_error(av[0], "", UNKNOW_ARG, 1));
			av[i] = NULL;
			n++;
		}
		i++;
	}
	del_null_params(*ac, av);
	*ac -= n;
	return (0);
}
