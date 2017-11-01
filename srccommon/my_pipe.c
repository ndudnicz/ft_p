/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndudnicz <ndudnicz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 17:43:24 by ndudnicz          #+#    #+#             */
/*   Updated: 2017/11/01 17:43:27 by ndudnicz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>

int		my_pipe(int fd1, int fd2)
{
	dup2(fd2, fd1 /*STDOUT_FILENO*/);
	// dup2(sock, /*STDERR_FILENO*/);
	return (0);
}
