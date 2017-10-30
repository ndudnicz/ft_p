#include <unistd.h>

#include "config.h"

void	lls(t_config *config)
{
	execl(LS_PATH, LS_PATH, "-p", ".", NULL);
}
