/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42barcelona.    +#+  +:+       +#+        */
/*   By: proche-c <proche-c@student.42barcelona.  +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2023/08/20 23:06:26 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_compare_upper_lower(char *str, char *to_compare)
{
	int	x;

	x = 0;
	if (ft_strlen(str) != ft_strlen(to_compare))
		return (0);
	while (str[x])
	{
		if (str[x] > 'A' && str[x] < 'Z')
		{
			if ((str[x] + 32) != to_compare[x])
				return (0);
		}
		else if (str[x] != to_compare[x])
			return (0);
		x++;
	}
	return (1);
}

int	ft_has_char(char *str, char x)
{
	int	num_char;
	int	i;

	num_char = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == x)
			num_char++;
		i++;
	}
	if (num_char != 0)
		return (num_char);
	return (0);
}
