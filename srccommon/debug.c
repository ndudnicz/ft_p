/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndudnicz <ndudnicz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 14:57:06 by ndudnicz          #+#    #+#             */
/*   Updated: 2017/10/23 14:57:07 by ndudnicz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <arpa/inet.h>

#include "libft.h"
#include "config.h"
#include "config.h"
#include "packet.h"
#include "user_input.h"

void	my_free(int n, void *ptr)
{
	if (n > 1000)
		ft_putnbr_endl(n);
	free(ptr);
}
