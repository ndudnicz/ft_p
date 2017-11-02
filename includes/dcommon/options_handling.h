/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options_handling.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndudnicz <ndudnicz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 18:00:48 by ndudnicz          #+#    #+#             */
/*   Updated: 2017/11/01 18:00:49 by ndudnicz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPTIONS_HANDLING_H
# define OPTIONS_HANDLING_H

int		get_options(t_config *config, int *ac, char **av);
int		set_root_folder(t_config *config, char const *exec_name,
						char const *param);

#endif
