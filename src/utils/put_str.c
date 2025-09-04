/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_str.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42barcelona.    +#+  +:+       +#+        */
/*   By: proche-c <proche-c@student.42barcelona.  +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by vaguilar          #+#    #+#             */
/*   Updated: 2023/08/20 23:08:21 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_put_str_2(char *str1, char *str2, int nl, int fd)
{
	ft_putstr_fd(str1, fd);
	ft_putstr_fd(str2, fd);
	if (nl == TRUE)
		ft_putstr_fd("\n", fd);
}

void	ft_put_str_3(char *str1, char *str2, int nl, int fd)
{
	ft_putstr_fd(str1, fd);
	ft_putstr_fd("=", fd);
	ft_putstr_fd(str2, fd);
	if (nl == TRUE)
		ft_putstr_fd("\n", fd);
}
