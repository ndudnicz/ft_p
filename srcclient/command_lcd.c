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
#include <stdio.h>//

#include "config.h"
#include "packet.h"
#include "debug.h"
#include "libft.h"
#include "libftasm.h"
#include "error.h"
#include "my_syslimits.h"

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
		if (i < ft_array_length(aa))
			my_free(3,a[i]);
		if (i < ft_array_length(bb))
			my_free(4,b[i]);
		if (i < ft_array_length(cc))
			my_free(5,c[i]);
		i++;
	}
	my_free(6,a);
	my_free(7,b);
	my_free(8,c);
	return (0);
}

static int	valid_user_input(t_config *config, char const *root,
								char const *input, char const *cwd)
{
	int			cursor;
	int			i;
	char const	**array_root = (char const**)ft_strsplit(root, '/');
	char const	**array_input = (char const**)ft_strsplit(input , '/');
	char const	**array_cwd = (char const**)ft_strsplit(cwd, '/');

	i = 0;
	if (!array_root || !array_input || !array_cwd)
		return (ft_error("LCD", INTERNAL_ERROR, "client", 0) || 1);
	cursor = ft_array_length(array_cwd);
	while (array_input[i])
	{
		if (!ft_strcmp(array_input[i], ".."))
			cursor--;
		else
			cursor++;
		i++;
	}
	if (cursor < ft_array_length(array_root))
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
	ft_putendl(arg);
	if (getcwd(cwd, PATH_MAX) < 0)
		return (ft_error("LCD", INTERNAL_ERROR, "client", 0));
	if (data_len == 0)
		new_path = config->root;
	else if (arg[0] == '/')
		new_path = ft_strdup(arg);
	else
		new_path = ft_strjoin_free(ft_strjoin(cwd, "/"), arg, 1, 0);
	if (chdir(new_path) < 0)
		return (ft_error("ERROR", "LCD", INVALID_PATH, 0));
	if (getcwd(cwd, PATH_MAX) < 0)
		return (ft_error("LCD", INTERNAL_ERROR, "client", 0));
	if (data_len)
		my_free(9, new_path);
	printf("%s\n", CMD_LCD_SUCCESS);
	return (0);
}
