#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include "my_syslimits.h"
#include "config.h"
#include "error.h"
#include "libft.h"
#include "libftasm.h"

static int	free_all_split(char const **aa, char const **bb)
{
	int		i;
	char	**a;
	char	**b;

	a = (char**)aa;
	b = (char**)bb;
	i = 0;
	while (a[i] || b[i])
	{
		if (i < ft_array_length(aa))
			free(a[i]);
		if (i < ft_array_length(bb))
			free(b[i]);
		i++;
	}
	free(a);
	free(b);
	return (0);
}

static int	valid_path(char const *cwd, char const *input)
{
	int			cursor;
	int			i;
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
		i++;
	}
	if (cursor <= ft_array_length(array_cwd))
		return (1);
	else
		return (free_all_split(array_input, array_cwd));
}

static int	ret_close(int const fd, char const in)
{
	int const	ret = (in && fd < 0) || (!in && fd > 0) ? 1 : 0;

	if (fd > 0)
		close(fd);
	return (ret);
}

int		valid_filename(char const *filename, char const in)
{
	char	cwd[PATH_MAX];
	char	*path_file;
	int		fd;

	if (getcwd(cwd, PATH_MAX) < 0)
		return (1);
	if (valid_path(cwd, filename) > 0)
		return (1);
	path_file = ft_strjoin_free(ft_strjoin(cwd, "/"), filename, 1, 0);
	fd = open(path_file, O_RDONLY);
	// printf("%s\nfd:%d\n", path_file, fd);
	return (ret_close(fd, in));
}
