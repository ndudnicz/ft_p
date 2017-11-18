/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_local.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndudnicz <ndudnicz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 17:59:30 by ndudnicz          #+#    #+#             */
/*   Updated: 2017/11/01 17:59:31 by ndudnicz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_CMD_LOCAL_H
# define EXEC_CMD_LOCAL_H

void	exec_cmd_local(unsigned short cmd, char const *arg);
void	exec_cmd_local_no_fork(t_config *config, t_input *input);

#endif
