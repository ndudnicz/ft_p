/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_lcd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndudnicz <ndudnicz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 13:49:36 by ndudnicz          #+#    #+#             */
/*   Updated: 2017/11/01 17:42:08 by ndudnicz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

#include "config.h"
#include "packet.h"
#include "debug.h"
#include "libft.h"
#include "libftasm.h"
#include "error.h"
#include "my_syslimits.h"

int		lcd(t_config *config, char *arg)
{
	char		*new_path;
	char		cwd[PATH_MAX];
	int const	data_len = ft_strlen(arg);

	cwd[0] = 0;
	ft_putendl(arg);
	if (getcwd(cwd, PATH_MAX) < 0)
		return (ft_error("LCD", INTERNAL_ERROR, "client", 0));
	if (data_len == 0)
		new_path = config->root;
	else if (arg[0] == '/')
		new_path = ft_strdup(arg);
	else
		new_path = ft_strjoin_free(ft_strjoin(cwd, "/"), arg, 1, 0);
	if (chdir(new_path) < 0)
		return (ft_error("ERROR", "LCD", INVALID_PATH, 0));
	if (getcwd(cwd, PATH_MAX) < 0)
		return (ft_error("LCD", INTERNAL_ERROR, "client", 0));
	if (data_len)
		my_free(9, new_path);
	printf("%s\n", CMD_LCD_SUCCESS);
	return (0);
}
