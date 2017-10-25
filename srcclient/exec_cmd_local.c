#include <unistd.h>
#include <stdlib.h>

#include "packet.h"
#include "config.h"
#include "user_input.h"
#include "command.h"
// #include "my_pipe.h"

void	exec_cmd_local(t_config *config, unsigned short cmd)
{
	if (cmd == ST_LLS)
		execl(LS_PATH, LS_PATH, "-p", config->current_path, NULL);
	else
		exit(0);
}

int		exec_cmd_local_no_fork(t_config *config, t_input *input)
{
	if (input->cmd == ST_LCD)
		lcd(config, input->arg);
}
