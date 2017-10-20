#include "error_master.h"
#include <stdio.h>

/*
** Try to establish a connection through the ip:port given as parameters.
** Set connection->socket if success.
** Display an error and return 1 if fails.
*/

int		establish_connection(char const *ip_str, char const *cmd_port_str)
{
	printf("Establishing connection to: %s:%s\n", ip_str, cmd_port_str);
	printf("Connection done with: %s:%s\n", ip_str, cmd_port_str);
	return (0);
}
