/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_filename.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndudnicz <ndudnicz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 17:45:19 by ndudnicz          #+#    #+#             */
/*   Updated: 2017/11/01 17:45:20 by ndudnicz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#include "my_syslimits.h"
#include "config.h"
#include "packet.h"
#include "error.h"
#include "libft.h"
#include "libftasm.h"
#include "debug.h"

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

static int	valid_path(t_config *config, char const *cwd, char const *input)
{
	int			cursor;
	int			i;
	char const	**array_root = (char const**)ft_strsplit(config->root, '/');
	char const	**array_input = (char const**)ft_strsplit(input, '/');
	char const	**array_cwd = (char const**)ft_strsplit(cwd, '/');

	i = 0;
	if (!array_input || !array_cwd)
		return (1);
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
	if (cursor <= ft_array_length(array_cwd))
		return (1);
	else
		return (free_all_split(array_input, array_cwd, array_root));
}

static int	ret_close(int const fd, char const in, char *path)
{
	int const	ret = (in && fd < 0) || (!in && fd > 0) ? 1 : 0;
	struct stat stat;

	if (fd > 0 && fstat(fd, &stat) < 0)
		return (-1);
	if (fd > 0)
		close(fd);
	if (path)
		free(path);
	return (((stat.st_mode & S_IFREG) && ret && in) || (ret));
}

int			valid_filename(t_config *config, char const *filename,
							char const in)
{
	char	cwd[PATH_MAX];
	char	*path_file;
	int		fd;

	if (!getcwd(cwd, PATH_MAX))
		return (-1);
	if (valid_path(config, cwd, filename) > 0)
		return (-1);
	path_file = ft_strjoin_free(ft_strjoin(cwd, "/"), filename, 1, 0);
	if (!path_file)
		return (-1);
	fd = open(path_file, O_RDONLY);
	return (ret_close(fd, in, path_file));
}
