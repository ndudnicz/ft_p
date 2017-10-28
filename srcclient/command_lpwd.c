#include <stdlib.h>
#include <stdio.h>

#include "libftasm.h"
#include "libft.h"//
#include "config.h"
#include "packet.h"
#include "error.h"
#include "my_syslimits.h"

/*
** Get the current working directory and display it on stdout
*/

int		lpwd(void)
{
	char	pwd[PATH_MAX];

	if (getcwd(pwd, PATH_MAX))
		printf("%s\n", pwd);
	else
		ft_error_child(INTERNAL_ERROR, "", "");
	return (0);
}
