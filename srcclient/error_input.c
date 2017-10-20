#include "libftasm.h"

/*
** Display an error message and does nothing.
*/

void	ft_error_input(char const *cmd, char const *filename, char const *type)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(filename, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(type, 2);
	ft_putstr_fd("\n", 2);
}
