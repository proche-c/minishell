/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2023/07/05 21:32:30 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_quotes(char *str, int start, int end, char *q)
{
	int	quotes;
	int	dquotes;

	quotes = 0;
	dquotes = 0;
	while (start < end)
	{
		if (str[start] == '\'' && q[start] == '0' && dquotes % 2 == 0)
			quotes++;
		else if (str[start] == '"' && q[start] == '0' && quotes % 2 == 0)
			dquotes++;
		start++;
	}
	return (quotes);
}

int	ft_count_dquotes(char *str, int start, int end, char *q)
{
	int	quotes;
	int	dquotes;

	quotes = 0;
	dquotes = 0;
	while (start < end)
	{
		if (str[start] == '\'' && q[start] == '0' && dquotes % 2 == 0)
			quotes++;
		else if (str[start] == '"' && q[start] == '0' && quotes % 2 == 0)
			dquotes++;
		start++;
	}
	return (dquotes);
}

void	ft_eval_quotes_value(char *value, int i, t_quo *initial, t_quo *auxq)
{
	int		j;
	t_quo	*new_quo;

	j = 0;
	while (value[j] != '\0')
	{
		if (value[j] == '"' || value[j] == '\'')
		{
			if (initial->first == 1)
			{
				initial->pos = i + j;
				initial->first = 2;
				auxq = initial;
			}
			else
			{
				new_quo = ft_new_quo();
				new_quo->pos = i + j;
				auxq->next = new_quo;
				auxq = new_quo;
			}
		}
		j++;
	}
}

char	*ft_get_real_quotes(t_quo *quo, t_master *master, int len)
{
	char	*result;
	int		i;

	result = malloc(sizeof(char) * (len + 1));
	if (result != NULL && master->error == 0)
	{
		i = 0;
		while (i < len)
			result[i++] = '0';
		result[i] = '\0';
	}
	ft_get_val_quo(quo, result);
	return (result);
}

void	ft_get_val_quo(t_quo *quo, char *result)
{
	t_quo	*initial;

	initial = quo;
	if (initial->first != 2)
		return ;
	while (initial != NULL)
	{
		result[initial->pos] = '1';
		initial = initial->next;
	}
}
