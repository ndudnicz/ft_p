/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndudnicz <ndudnicz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 18:05:04 by ndudnicz          #+#    #+#             */
/*   Updated: 2017/11/01 18:05:06 by ndudnicz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H

void	ls(t_config *config);
void	cd(t_config *config, t_packet *packet);
void	pwd(t_config *config, t_packet *packet);
int		put(t_config *config, t_packet *packet);
int		get(t_config *config, t_packet *packet);

#endif
