#ifndef OPEN_CONNECTION_H
# define OPEN_CONNECTION_H

int		open_cmd_connection(t_config *config, char const *cmd_port_str);
int		open_data_connection(t_config *config, t_packet *packet,
					int (*transfert)(t_config*, char const*));

#endif
