#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include "config.h"
#include "error.h"

/*
** Try to establish a data connection through the new port
** given as parameters, by the server.
** Return 0 if success
** Display an error and return 1 if fails.
*/

int			establish_data_connection(t_config *config, char const *filename,
				int (*transfert)(t_config*, char const*),
				int (*error_handler)(t_config*, char const*, char const*))
{
	struct protoent		*proto;
	struct sockaddr_in	sin;

	if ((proto = getprotobyname("tcp")) == 0)
		return (error_handler(config, "establish_data_connection()", GETPROTOBYNAME_FAIL));
	/*CONFIG INIT*/

	if ((config->socket.data = socket(PF_INET, SOCK_STREAM, proto->p_proto)) < 0)
		return (error_handler(config, "establish_data_connection()", SOCKET_FAILED));
	config->port.data = htons(config->port.data);

	/*SIN INIT*/
	sin.sin_family = AF_INET;
	sin.sin_port = config->port.data;
	sin.sin_addr.s_addr = config->inet_addr;
	printf("data connecting ...\n");
	if (connect(config->socket.data, (const struct sockaddr*)&sin, sizeof(sin)) < 0)
		return (error_handler(config, "establish_connection()", CONNECT_ERROR));
	printf("data Connection done\n");
	transfert(config, filename);
	return (0);
}
