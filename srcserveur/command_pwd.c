#include <stdlib.h>
#include <unistd.h>

#include "libftasm.h"
#include "libft.h"//
#include "config.h"
#include "packet.h"
#include "send_message.h"
#include "error_message.h"
#include "my_syslimits.h"

/*
** Get the current working directory and send it to the client
*/

void	pwd(t_config *config, t_packet *packet)
{
	char	pwd[PATH_MAX];

	if (getcwd(pwd, PATH_MAX))
		send_message(config, pwd, "Server");
	else
		send_message(config, INTERNAL_ERROR, "Server");
	exit(0);
}
