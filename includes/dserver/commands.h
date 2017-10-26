#ifndef COMMANDS_H
# define COMMANDS_H

void	ls(t_config *config);
void	cd(t_config *config, t_packet *packet);
void	pwd(t_config *config, t_packet *packet);
int		put(t_config *config, t_packet *packet);

#endif
