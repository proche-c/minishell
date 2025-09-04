/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   returns.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42barcelona.    +#+  +:+       +#+        */
/*   By: proche-c <proche-c@student.42barcelona.  +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2023/08/20 23:08:23 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_return_error(char *str1, char *str2)
{
	char	*join;

	join = ft_strjoin(str1, str2);
	ft_putstr_fd(join, 2);
	free(join);
}

void	ft_return_error_3(char *str1, char *str2, char *str3)
{
	char	*join1;
	char	*join2;

	join1 = ft_strjoin(str1, str2);
	join2 = ft_strjoin(join1, str3);
	ft_putstr_fd(join2, 2);
	free(join1);
	free(join2);
}
