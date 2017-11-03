/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndudnicz <ndudnicz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 17:59:15 by ndudnicz          #+#    #+#             */
/*   Updated: 2017/11/01 17:59:18 by ndudnicz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H

int		lcd(t_config *config, char *arg);
int		lpwd(void);
int		put(t_config *config, t_packet *packet, char const *filename);
int		put_check_local_file(char const *filename);
int		get(t_config *config, t_packet *packet, char const *filename);
int		get_check_local_file(char const *filename);

void	lls(void);

#endif
