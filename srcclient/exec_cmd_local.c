#include <unistd.h>
#include <stdlib.h>

#include "config.h"
#include "packet.h"
#include "user_input.h"
#include "commands.h"
// #include "my_pipe.h"

void	exec_cmd_local(t_config *config, unsigned short cmd)
{
	if ((cmd & ST_MASK) == ST_LLS)
		lls(config);
	else
		exit(0);
}

int		exec_cmd_local_no_fork(t_config *config, t_input *input)
{
	if (input->cmd == ST_LCD)
		return (lcd(config, input->arg));
	else if (input->cmd == ST_LPWD)
		return (lpwd());
	else
		return (0);
}
