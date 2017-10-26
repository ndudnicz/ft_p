#include <stdlib.h>
#include <stdio.h>

#include "libftasm.h"
#include "libft.h"//
#include "config.h"
#include "packet.h"
#include "error_message.h"
#include "error_child.h"
#include "my_syslimits.h"

/*
** Get the current working directory and send it to the client
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
