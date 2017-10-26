#ifndef SWITCH_PACKET_TYPE_SERVER_H
# define SWITCH_PACKET_TYPE_SERVER_H

int		switch_packet_type_server(t_config *config, t_packet *packet);
void	switch_packet_type_server_no_fork(t_config *config, t_packet *packet);

#endif
