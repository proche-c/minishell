/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tilde.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veaz <veaz@student.42.fr>                  +#+  +:+       +#+        */
/*   By: proche-c <proche-c@student.42barcelona.  +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2023/06/03 21:58:24 by veaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_tilde(char *str, int i)
{
	if (i == 0)
	{
		while (ft_isspace(str[i]) == 1)
			i++;
		if (str[i] == '~' && (ft_isspace(str[i + 1]) == 1
				|| str[i + 1] == '\0' || str[i + 1] == '/'))
		{
			return (1);
		}
		else
			return (0);
	}
	else
	{
		if (ft_is_quoted(str, i) == 0 && str[i] == '~'
			&& ft_isspace(str[i - 1]) == 1 && (ft_isspace(str[i + 1]) == 1
				|| str[i + 1] == '\0' || str[i + 1] == '/'))
			return (1);
		else
			return (0);
	}
}

int	ft_with_tilde(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_is_tilde(str, i) == 1)
			return (1);
		i++;
	}
	return (0);
}
