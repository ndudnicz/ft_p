#include <unistd.h>
#include <stdlib.h>

#include "packet.h"
#include "config.h"
// #include "my_pipe.h"

void	exec_cmd_local(t_config *config, unsigned short cmd)
{
	if (cmd == ST_LLS)
	{
		execl("/bin/ls", "ls", "-p", config->current_path, NULL);
	}
	else
		exit(0);
}
