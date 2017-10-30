#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>//
#include <sys/time.h>//
#include <sys/resource.h>//
#include <sys/wait.h>//

#include "libft.h"
#include "libftasm.h"
#include "config.h"
#include "user_input.h"
#include "packet.h"
#include "debug.h"//
#include "send_packet.h"
#include "receive_packet.h"
#include "switch_packet_type_client.h"
#include "error.h"//
#include "exec_cmd_local.h"
#include "commands.h"

static unsigned short get_type(char const *str, char const *arg)
{
	unsigned int const	arg_len = ft_strlen(arg);

	if (!str)
		return ((unsigned short)ft_error("ERROR", "INPUT", UNKNOWN_CMD, 0));
	else if (!ft_strcmp_nocase("quit", str) && arg_len == 0)
		return (ST_QUIT);
	else if (!ft_strcmp_nocase("ls", str) && arg_len == 0)
		return (ST_LS);
	else if (!ft_strcmp_nocase("cd", str))
		return (ST_CD);
	else if (!ft_strcmp_nocase("get", str))
		return (ASK_NEW_DATA_CONNECTION | ST_GET);
	else if (!ft_strcmp_nocase("put", str))
		return (ASK_NEW_DATA_CONNECTION | ST_PUT);
	else if (!ft_strcmp_nocase("pwd", str) && arg_len == 0)
		return (ST_PWD);
	else if (!ft_strcmp_nocase("lls", str) && arg_len == 0)
		return (ST_LLS);
	else if (!ft_strcmp_nocase("lcd", str))
		return (ST_LCD);
	else if (!ft_strcmp_nocase("lpwd", str) && arg_len == 0)
		return (ST_LPWD);
	else
		return ((unsigned short)ft_error("ERROR", "INPUT", UNKNOWN_CMD, 0));
}

static void				sub_free(void *p1, void *p2)
{
	if (p1)
		free(p1);
	if (p2)
		free(p2);
}

static unsigned short	treat_input(t_input *input, char *line)
{
	char const	*s = ft_strtrim(line);
	char const	**array = (char const**)ft_strsplit(s, ' ');
	int			i;

	i = 0;
	input->arg = NULL;
	if (line)
		free(line);
	if (!array)
		return (0);
	if (ft_array_length(array) > 1)
		input->arg = (char*)array[1];
	else
		input->arg = ft_strdup("");
	input->cmd = get_type(array[0], input->arg);
	while (array[i])
	{
		if (i != 1)
			free((void*)array[i]);
		i++;
	}
	sub_free((void*)array, (void*)s);
	return (input->cmd);
}


/*
** Loop and treat the input string while the user doesn't type 'quit' or press
** CTRL-D
*/
/*
int		user_input_loop(t_config *config)
{
	char		*line;
	int			pid;
	t_packet	*packet;
	t_input		input;
	int			stat_loc;

	if (!(packet = (t_packet*)malloc(sizeof(t_packet))))
		return (ft_error("Error", "user_input_loop()", MALLOC_FAIL, 1));
	line = NULL;
	while (ft_putstr(PROMPT) && gnl(0, &line) > 0)
	{
		if (treat_input(&input, line) == ST_QUIT)
			break ;
		if (input.arg && input.cmd && !(input.cmd & ST_CMD_LOCAL))
		{
			if ((input.cmd == ST_PUT && put_check_local_file(input.arg) > 0) ||
			(input.cmd == ST_GET && get_check_local_file(input.arg) > 0))
			{
				if (input.arg)
					free(input.arg);
				continue ;
			}
			forge_packet(packet, (HEADER_SIZE + ft_strlen(input.arg)) << 16 |
			input.cmd, input.arg, 1);
			send_packet(config->socket.cmd, packet);
			receive_packet(config, config->socket.cmd, packet);
			if (switch_packet_type_client(config, packet, input.arg) > 0)
				return (1);
			ft_bzero((char*)packet, packet->size);
		}
		else if (input.cmd)
		{
			if (should_fork(input.cmd) > 0)
			{
				pid = fork();
				if (pid == 0)
					exec_cmd_local(config, input.cmd);
				else
					wait4(pid, &stat_loc, 0, NULL);
			}
			else
				exec_cmd_local_no_fork(config, &input);
		}
		if (input.arg)
			free(input.arg);
	}
	free(packet);
	ft_putendl("Bye!");
	return (0);
}
*/

int		user_input_loop(t_config *config)
{
	char		*line;
	int			pid;
	t_packet	*packet;
	t_input		input;
	int			stat_loc;

	if (!(packet = (t_packet*)malloc(sizeof(t_packet))))
		return (ft_error("Error", "user_input_loop()", MALLOC_FAIL, 1));
	line = NULL;
	input.arg = NULL;
	while (ft_putstr(PROMPT) && gnl(0, &line) > 0)
	{
		if (input.arg)
			free(input.arg);
		if (treat_input(&input, line) == ST_QUIT)
			break ;
		if (input.arg && input.cmd && !(input.cmd & ST_CMD_LOCAL))
		{
			ft_putendl("non local");
			if ((input.cmd == ST_PUT && put_check_local_file(input.arg) > 0) ||
			(input.cmd == ST_GET && get_check_local_file(input.arg) > 0))
				continue ;
			forge_packet(packet, (HEADER_SIZE + ft_strlen(input.arg)) << 16 |
			input.cmd, input.arg, 1);
			send_packet(config->socket.cmd, packet);
			receive_packet(config, config->socket.cmd, packet);
			if (switch_packet_type_client(config, packet, input.arg) > 0)
				return (1);
			ft_bzero((char*)packet, packet->size);
		}
		else if (input.cmd)
		{
			ft_putendl("local");
			fork_and_run(config, &input);

		}
	}
	free(packet);
	ft_putendl("Bye!");
	return (0);
}
