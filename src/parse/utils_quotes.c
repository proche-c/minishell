/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veaz <veaz@student.42.fr>                  +#+  +:+       +#+        */
/*   By: proche-c <proche-c@student.42barcelona.  +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2023/05/30 09:52:00 by veaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_find_quote(char *str, int j, int end)
{
	int	i;
	int	quote;
	int	dquote;

	quote = 0;
	dquote = 0;
	i = 0;
	while (str[i] != '\0' && i <= end)
	{
		if (str[i] == '\'' && dquote % 2 == 0)
			quote++;
		else if (str[i] == '"' && quote % 2 == 0)
			dquote++;
		i++;
	}
	if (j == 1)
		return (quote);
	else
		return (dquote);
}

int	ft_is_quoted(char *str, int i)
{
	int	quote;
	int	d_quote;

	if (str[i] == '\'' || str[i] == '"')
		return (3);
	else if (i == 0)
		return (0);
	else
	{
		quote = ft_find_quote(str, 1, i - 1);
		d_quote = ft_find_quote(str, 0, i - 1);
	}
	if ((quote % 2 == 0 || quote == 0)
		&& (d_quote % 2 == 0 || d_quote == 0))
		return (0);
	else
		return (1);
}

int	ft_find_quote_rev(char *str, int i)
{
	int	end;
	int	quote;
	int	dquote;
	int	result;

	result = 0;
	end = ft_strlen(str) - 1;
	quote = 0;
	dquote = 0;
	while (end > i)
	{
		if (str[end] == '\'' && dquote % 2 == 0)
			quote++;
		else if (str[end] == '"' && quote % 2 == 0)
			dquote++;
		end--;
	}
	if (quote % 2 != 0)
		result = 1;
	return (result);
}

int	ft_find_dquote_rev(char *str, int i)
{
	int	end;
	int	quote;
	int	dquote;
	int	result;

	result = 0;
	end = ft_strlen(str) - 1;
	quote = 0;
	dquote = 0;
	while (end > i)
	{
		if (str[end] == '\'' && dquote % 2 == 0)
			quote++;
		else if (str[end] == '"' && quote % 2 == 0)
			dquote++;
		end--;
	}
	if (dquote % 2 != 0)
		result = 1;
	return (result);
}

int	ft_find_quotes_rev(char *str, int i)
{
	if ((ft_find_quote_rev(str, i) == 0 || ft_find_quote_rev(str, i) % 2 == 0)
		&& (ft_find_dquote_rev(str, i) == 0
			|| ft_find_dquote_rev(str, i) % 2 == 0))
		return (0);
	else
		return (1);
}
