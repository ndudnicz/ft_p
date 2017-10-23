#ifndef CONFIG_H
# define CONFIG_H

# define PROMPT "ftp> "

# define	PARAMS_STR "e"

/*
**
*/

# define LS_PATH	"/bin/ls"
# define LS_BIN		"ls"
# define CD_PATH	"/usr/bin/cd"

/*
** ========= S_PORT ============================================================
**
** Server side:
**   t_port.cmd = command port listening, to establish new connection or
**                communicate with a client (no data stuff)
**   t_port.data = data port, for data transfers (in & out).
**
** Client side:
**   t_port.cmd = command port, to send all commands to the server except
**                data stuff
**   t_port.data = data port, for data transfers (in & out).
*/

typedef struct	s_port
{
	int		cmd;
	int		data;
}				t_port;

/*
** ========= S_SOCKET ==========================================================
**
** Server side:
**   t_socket.server_master = main socket listening
**   t_socket.cmd = client socket
**   t_socket.data = data transfer socket
**
** Client side:
**   t_socket.server_master is not used.
**   t_socket.cmd = command socket
**   t_socket.data = data transfer socket
*/

typedef struct	s_socket
{
	int		cmd;
	int		data;
	int		server_master;
}				t_socket;

typedef struct	s_config // malloc
{
	unsigned char	options;
	int				inet_addr;
	char			*ip_addr_str;
	char			*current_path; // malloc
	char			*buf;  // malloc
	char			*tmp_file_str;  // malloc
	t_socket		socket;
	t_port			port;
}				t_config;

t_config	*configdup(t_config *c);

#endif
