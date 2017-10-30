#ifndef OPEN_DATA_CONNECTION_H
# define OPEN_DATA_CONNECTION_H

int		open_data_connection(t_config *config, t_packet *packet,
					int (*transfert)(t_config*, char const*));

#endif
