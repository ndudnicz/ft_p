/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndudnicz <ndudnicz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 13:49:36 by ndudnicz          #+#    #+#             */
/*   Updated: 2017/10/25 13:49:37 by ndudnicz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "config.h"
#include "packet.h"
#include "send_message.h"
#include "debug.h"
#include "libft.h"
#include "libftasm.h"
#include "error.h"
#include "my_syslimits.h"

static int	free_all_split(char const **aa,
							char const **bb,
							char const **cc)
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
			my_free(20, a[i]);
		if (i < ft_array_length(bb))
			my_free(21, b[i]);
		if (i < ft_array_length(cc))
			my_free(22, c[i]);
		i++;
	}
	my_free(23, a);
	my_free(24, b);
	my_free(25, c);
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
		return (send_message(config, INTERNAL_ERROR, "serveur") || 1);
	cursor = ft_array_length(array_cwd);
	while (array_input[i])
	{
		if (!ft_strcmp(array_input[i], ".."))
			cursor--;
		else
			cursor++;
		if (cursor < ft_array_length(array_root))
			return (1);
		i++;
	}
	if (cursor < ft_array_length(array_root))
		return (1);
	else
		return (free_all_split(array_root, array_input, array_cwd));
}

static int	ret_norme(t_config *config, int n, char *new_path)
{
	my_free(n, new_path);
	return (send_message(config, CMD_CD_INVALID_PATH, "serveur"));
}

int			cd(t_config *config, t_packet *packet)
{
	char		*new_path;
	char		cwd[PATH_MAX];
	char		oldcwd[PATH_MAX];
	int const	data_len = ft_strlen(packet->data);

	packet->data[packet->size - HEADER_SIZE] = 0;
	if (!getcwd(oldcwd, PATH_MAX))
		return (send_message(config, INTERNAL_ERROR, "serveur"));
	if (valid_user_input(config, config->root, packet->data, oldcwd) > 0)
		return (send_message(config, CMD_CD_INVALID_PATH, "serveur"));
	if (data_len == 0)
		new_path = ft_strdup(config->root);
	else
		new_path = ft_strjoin_free(ft_strjoin(oldcwd, "/"), packet->data, 1, 0);
	if (chdir(new_path) < 0)
		return (ret_norme(config, 26, new_path));
	if ((!getcwd(cwd, PATH_MAX) || !(ft_strstr(cwd, config->root) == cwd))
	&& chdir(oldcwd) + 2)
		return (ret_norme(config, 27, new_path));
	my_free(27, new_path);
	if (!getcwd(cwd, PATH_MAX))
		return (send_message(config, INTERNAL_ERROR, "serveur"));
	else
		return (send_message(config, CMD_CD_SUCCESS, "serveur"));
}
