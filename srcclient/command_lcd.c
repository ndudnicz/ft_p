/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_lcd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndudnicz <ndudnicz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 13:49:36 by ndudnicz          #+#    #+#             */
/*   Updated: 2017/10/25 13:49:37 by ndudnicz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/syslimits.h>

#include "config.h"
#include "packet.h"
#include "debug.h"
#include "libft.h"
#include "libftasm.h"
#include "error_message.h"
#include "error_master.h"

static int	array_length(char const **array)
{
	int		i;

	i = 0;
	while (array && array[i])
		i++;
	return (i);
}

static int	free_all_split(char const **aa, char const **bb, char const **cc)
{
	int		i;
	char	**a;
	char	**b;
	char	**c;

	a = (char**)aa;
	b = (char**)bb;
	c = (char**)cc;
	i = 0;
	while (a[i] || b[i] || c[i])
	{
		if (i < array_length(aa))
			free(a[i]);
		if (i < array_length(bb))
			free(b[i]);
		if (i < array_length(cc))
			free(c[i]);
		i++;
	}
	free(a);
	free(b);
	free(c);
	return (0);
}

static int	valid_user_input(t_config *config, char const *root,
								char const *input, char const *cwd)
{
	int			cursor;
	int			i;
	char const	**array_root = (char const**)ft_strsplit(root, '/');
	char const	**array_input = (char const**)ft_strsplit(input, '/');
	char const	**array_cwd = (char const**)ft_strsplit(cwd, '/');

	i = 0;
	if (!array_root || !array_input || !array_cwd)
		return (ft_error("LCD", INTERNAL_ERROR, "client", 0) || 1);
	cursor = array_length(array_cwd);
	while (array_input[i])
	{
		if (!ft_strcmp(array_input[i], ".."))
			cursor--;
		else
			cursor++;
		i++;
	}
	if (cursor < array_length(array_root))
		return (1);
	else
		return (free_all_split(array_root, array_input, array_cwd));
}

int			lcd(t_config *config, char *arg)
{
	char		*new_path;
	char		cwd[PATH_MAX];
	int const	data_len = ft_strlen(arg);

	cwd[0] = 0;
	if (getcwd(cwd, PATH_MAX) < 0)
		return (ft_error("LCD", INTERNAL_ERROR, "client", 0));
	if (valid_user_input(config, config->root, arg, cwd) > 0)
		return (ft_error("LCD", CMD_CD_INVALID_PATH, "client", 0));
	if (data_len == 0)
		new_path = config->root;
	else
		new_path = ft_strjoin_free(ft_strjoin(cwd, "/"), arg, 1, 0);
	if (chdir(new_path) < 0)
		return (ft_error("LCD", CMD_CD_SUCCESS, "client", 0));
	if (getcwd(cwd, PATH_MAX) < 0)
		return (ft_error("LCD", INTERNAL_ERROR, "client", 0));
	if (data_len)
		free(new_path);
	return (ft_error("LCD", CMD_CD_SUCCESS, "client", 0));
}
