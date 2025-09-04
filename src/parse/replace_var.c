/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veaz <veaz@student.42.fr>                  +#+  +:+       +#+        */
/*   By: proche-c <proche-c@student.42barcelona.  +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2023/05/30 09:37:05 by veaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_has_dollar(char *str)
{
	int	dollar;
	int	x;

	x = 0;
	dollar = 0;
	while (str[x] != '\0')
	{
		if (str[x] == '$')
		{
			dollar++;
		}
		x++;
	}
	if (dollar > 0)
		return (dollar);
	return (0);
}

char	*ft_search_var(char *str)
{
	char	*var;
	int		start;
	int		x;

	x = 0;
	start = 0;
	var = NULL;
	while (str[start] != '$')
		start++;
	start++;
	x = start;
	while (str[x] != '\0' && str[x] != '\'' && str[x] != '\"')
		x++;
	var = ft_substr(str, start, x - start);
	return (var);
}

int	ft_len_var(char *str, int i)
{
	int		len_var;

	len_var = 0;
	i++;
	if ((str[i] == '\'' || str[i] == '"')
		&& (ft_find_dquote_rev(str, i - 1) % 2 == 0
			|| ft_find_dquote_rev(str, i - 1) == 0))
	{
		len_var = ft_len_var_quoted(str, i);
	}
	else
	{
		while (str[i] != '\0' && str[i] != '\'' && str[i] != '"'
			&& str[i] != '$' && ft_isspace(str[i]) != 1 && str[i] != '='
			&& str[i] != ',' && str[i] != '|' && str[i] != '/'
			&& str[i] != '<' && str[i] != '>')
		{
			len_var++;
			i++;
		}
	}
	return (len_var);
}

int	ft_len_var_quoted(char *str, int i)
{
	char	c;
	int		len_var;

	c = str[i];
	i++;
	len_var = 1;
	while (str[i] != c)
	{
		len_var++;
		i++;
	}
	len_var++;
	return (len_var);
}
