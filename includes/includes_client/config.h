#ifndef CONFIG_H
# define CONFIG_H

# define	PARAMS_STR "e"

typedef struct	s_port
{
	int		cmd;
	int		data;
}				t_port;

typedef struct	s_socket
{
	int		cmd;
	int		data;
}				t_socket;

typedef struct	s_config
{
	unsigned char	options;
	int				inet_addr;
	char			*ip_addr_str;
	t_socket		socket;
	t_port			port;
}				t_config;

#endif
