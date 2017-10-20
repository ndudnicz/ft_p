#include "error.h"
#include "libftasm.h"



int		ft_error(char const *exec_name, char const *filename, char const *type, int ret)
{
	char	*joined_msg;

	ft_putstr_fd(exec_name, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(filename, 2);
	ft_putstr_fd(type, 2);
	ft_putstr_fd("\n", 2);
	return (-1);
}
