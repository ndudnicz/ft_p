#ifndef ESTABLISH_DATA_CONNECTION_H
# define ESTABLISH_DATA_CONNECTION_H

int			establish_data_connection(t_config *config, char const *filename,
				int (*transfert)(t_config*, char const*),
				int (*error_handler)(t_config*, char const*, char const*));

#endif
