#include <stdlib.h>
#include <sys/syslimits.h>
// #include <linux/limits.h>//

#include "libftasm.h"
#include "libft.h"//
#include "config.h"
#include "packet.h"
#include "send_message.h"

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
