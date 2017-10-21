#ifndef ESTABLISH_CONNECTION_H
# define ESTABLISH_CONNECTION_H

# include "config.h"

int		establish_connection(t_config *config, char const *ip_str,
								char const *cmd_port_str);

#endif
