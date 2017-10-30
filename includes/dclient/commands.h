#ifndef COMMANDS_H
# define COMMANDS_H

int		lcd(t_config *config, char *arg);
int		lpwd(void);
int		put(t_config *config, t_packet *packet, char const *filename,
			char const *remote_filename);
int		put_check_local_file(char const *filename);
int		get(t_config *config, t_packet *packet, char const *filename);
int		get_check_local_file(char const *filename);

void	lls(t_config *config);

#endif
