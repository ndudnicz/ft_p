#include <stdlib.h>
// #include <sys/syslimits.h>
#include <linux/limits.h>//

#include "libftasm.h"
#include "libft.h"//
#include "config.h"
#include "packet.h"
#include "send_message.h"

void	pwd(t_config *config, t_packet *packet)
{
	char	pwd[PATH_MAX];

	if (getcwd(pwd, PATH_MAX))
	{
		send_message(config, pwd, "Server");
	}
	else
		send_message(config, "ERROR", "Server");
	exit(0);
}
