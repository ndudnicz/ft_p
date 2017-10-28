#include <fcntl.h>
#include <unistd.h>

#include "config.h"
#include "packet.h"
#include "debug.h"
#include "error.h"
#include "send_data.h"
#include "my_syslimits.h"
#include "establish_data_connection.h"
#include "libft.h"
#include "libftasm.h"

int		put(t_config *config, t_packet *packet, char const *filename, char const *remote_filename)
{
	char			cwd[PATH_MAX];
	char			*path;

	if (getcwd(cwd, PATH_MAX) < 0)
		return (ft_error("ERROR", "PUT", "GETCWD()", 1));
	path = ft_strjoin_free(ft_strjoin(cwd, "/"), filename, 1, 0);
	if (open(path, O_RDONLY) < 0)
		return (ft_error("ERROR", "PUT", INVALID_PATH, 1));
	config->port.data = ft_atoi(packet->data);
	establish_data_connection(config, filename, &send_data, &error_handler_local);
	return (0);
}