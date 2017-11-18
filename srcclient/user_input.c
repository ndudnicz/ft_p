/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndudnicz <ndudnicz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 17:42:50 by ndudnicz          #+#    #+#             */
/*   Updated: 2017/11/01 17:42:51 by ndudnicz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"
#include "libftasm.h"
#include "config.h"
#include "user_input.h"
#include "packet.h"
#include "debug.h"
#include "send_packet.h"
#include "receive_packet.h"
#include "switch_packet_type_client.h"
#include "error.h"
#include "exec_cmd_local.h"
#include "commands.h"

static unsigned short	get_type(char const *str, char const *arg)
{
	unsigned int const	arg_len = ft_strlen(arg);

	if (!str)
		return ((unsigned short)ft_error("ERROR", "INPUT", UNKNOWN_CMD, 0));
	else if (!ft_strcmp_nocase("quit", str) && arg_len == 0)
		return (ST_QUIT);
	else if (!ft_strcmp_nocase("ls", str))
		return (ST_LS);
	else if (!ft_strcmp_nocase("cd", str))
		return (ST_CD);
	else if (!ft_strcmp_nocase("get", str))
		return (ASK_NEW_DATA_CONNECTION | ST_GET);
	else if (!ft_strcmp_nocase("put", str))
		return (ASK_NEW_DATA_CONNECTION | ST_PUT);
	else if (!ft_strcmp_nocase("pwd", str) && arg_len == 0)
		return (ST_PWD);
	else if (!ft_strcmp_nocase("lls", str))
		return (ST_LLS);
	else if (!ft_strcmp_nocase("lcd", str))
		return (ST_LCD);
	else if (!ft_strcmp_nocase("lpwd", str) && arg_len == 0)
		return (ST_LPWD);
	else
		return ((unsigned short)ft_error("ERROR", "INPUT", UNKNOWN_CMD, 0));
}

static int				free_array(char **array, int i, int ret)
{
	if (array)
	{
		while (array[i])
		{
			my_free(16, (void*)array[i]);
			i++;
		}
		my_free(15, (void*)array);
	}
	return (ret);
}

static unsigned short	treat_input(t_input *input, char *line, int i)
{
	char const	**array = (char const**)ft_strsplit(line, ' ');

	input->arg = NULL;
	if (!line || !array)
		return (ft_error("ERROR", "treat_input()", MALLOC_FAIL, 1));
	if (line)
	{
		my_free(13, line);
		line = NULL;
	}
	if (ft_array_length(((char const**)array)) == 0)
		return (free_array((char**)array, i, 0));
	if (ft_array_length((char const**)array) > 1)
		input->arg = ft_strdup((char*)array[1]);
	else
		input->arg = ft_strdup("");
	if (!input->arg)
		return (ft_error("ERROR", "treat_input()", MALLOC_FAIL, 1));
	if (ft_strlen(array[0]) > PATH_MAX ||
	(input->arg && ft_strlen(input->arg) > PATH_MAX))
		return (0);
	input->cmd = get_type(array[0], input->arg);
	free_array((char**)array, i, 0);
	return (input->cmd);
}

static int				cmd_handling(t_config *config, t_input *input,
									t_packet *packet)
{
	t_size_type	size_type;

	if ((input->cmd == ST_PUT && put_check_local_file(input->arg) > 0)
	|| (input->cmd == ST_GET && get_check_local_file(input->arg) > 0))
		return (-1);
	size_type.size = HEADER_SIZE + ft_strlen(input->arg);
	size_type.type = input->cmd;
	forge_packet(packet, &size_type, input->arg, 1);
	send_packet(config->socket.cmd, packet);
	if (receive_packet(config, config->socket.cmd, packet, input->cmd) < 0)
		return (ft_error("ERROR", "SERVER SIDE", "CONNECTION LOST", 1));
	if (switch_packet_type_client(config, packet, input->arg) > 0)
		return (1);
	ft_bzero((char*)packet, packet->size);
	return (0);
}

/*
** Loop and treat the input string while the user doesn't type 'quit' or press
** CTRL-D
*/

int						user_input_loop(t_config *config, int ret, char *line)
{
	t_packet	*packet;
	t_input		input;

	if (!(packet = (t_packet*)malloc(sizeof(t_packet))))
		return (ft_error("Error", "user_input_loop()", MALLOC_FAIL, 1));
	input.arg = NULL;
	while (ft_putstr(PROMPT) && gnl(0, &line) > 0)
	{
		if (input.arg)
			my_free(17, input.arg);
		if (treat_input(&input, line, 0) == ST_QUIT)
			break ;
		if (input.arg && input.cmd && !(input.cmd & ST_CMD_LOCAL))
		{
			if ((ret = cmd_handling(config, &input, packet)) < 0)
				continue ;
			else if (ret)
				return (1);
		}
		else if (input.cmd)
			fork_and_run(config, &input);
	}
	close(config->socket.cmd);
	return (ft_putstr("Bye!\n") - 5);
}
