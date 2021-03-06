/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndudnicz <ndudnicz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 18:00:06 by ndudnicz          #+#    #+#             */
/*   Updated: 2017/11/01 18:00:08 by ndudnicz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

# include "my_syslimits.h"

# define PROMPT				"\033[90mftp>\033[39m "
# define DEFAULT_IP_BIND	"127.0.0.1"

/*
** Ephemeral port range,
** suggested by the Internet Assigned Numbers Authority (IANA).
** 49152 <= port <= 65535
** Used for data port definition.
*/

# define LOW_BOUND_PORT_RANGE	49152
# define HIGH_BOUND_PORT_RANGE	65535

/*
** Options
*/

# define ROOT_FOLDER		0x02
# define ROOT_FOLDER_CHAR	'f'
# define PARAMS_STR			"f"
# define LS_PATH			"/bin/ls"

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

typedef struct	s_config
{
	unsigned char	options;
	int				inet_addr;
	char			*ip_str;
	char			root[PATH_MAX];
	char			*buf;
	t_port			port;
	t_socket		socket;
}				t_config;

t_config		*create_config(char const*exec_name);

#endif
