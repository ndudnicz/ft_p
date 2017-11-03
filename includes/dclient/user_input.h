/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_input.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndudnicz <ndudnicz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 17:59:40 by ndudnicz          #+#    #+#             */
/*   Updated: 2017/11/01 17:59:42 by ndudnicz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_INPUT_H
# define USER_INPUT_H

typedef struct	s_input
{
	unsigned short	cmd;
	char			*arg;
}				t_input;

int				user_input_loop(t_config *config, int ret, char *line);
void			fork_and_run(t_config *config, t_input *input);

#endif
