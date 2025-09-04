/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2023/09/30 12:48:45 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_eval_end(char *str, int i, int quote, int d_quote)
{
	int	result;

	if (ft_char_resv(str, i) != 0 && d_quote % 2 == 0 && quote % 2 == 0)
		result = 1;
	else
		result = 0;
	return (result);
}

static int	ft_calculate_len(char *str, int i, int len)
{
	int	quote;
	int	d_quote;

	quote = 0;
	d_quote = 0;
	while (ft_eval_end(str, i, quote, d_quote) == 0 && str[i] != '\0')
	{
		if (str[i] == '\'')
			quote++;
		if (str[i] == '"')
			d_quote++;
		i++;
		len++;
	}
	len--;
	i--;
	while (ft_isspace(str[i]) == 1)
	{
		len--;
		i--;
	}
	return (len);
}

static int	ft_find_length(char *str, int i)
{
	int	len;

	len = 0;
	if (ft_char_resv(str, i) == 2)
		return (2);
	else if (ft_char_resv(str, i) == 1)
		return (1);
	else
		return (ft_calculate_len(str, i, len) + 1);
}

void	ft_assign_str_2(t_master *master, char *str, char **result)
{
	int	i;
	int	j;
	int	k;
	int	len;

	i = 0;
	j = 0;
	while (str[i] != '\0' && j < master->num_elem)
	{
		while (ft_isspace(str[i]) == 1 && str[i] != '\0')
			i++;
		len = ft_find_length(str, i);
		result[j] = (char *)malloc(sizeof(char) * (len + 1));
		if (!result[j])
			master->error = 1;
		k = 0;
		while (k < len && str[i] != '\0')
			result[j][k++] = str[i++];
		result[j][k] = '\0';
		j++;
	}
	result[j] = 0;
}

void	ft_separate_str(t_master *master)
{
	master->num_elem = ft_get_num_elem(master->str);
	master->elem = malloc(sizeof(char *) * (master->num_elem + 1));
	if (!master->elem)
		master->error = 1;
	else
		ft_assign_str_2(master, master->str, master->elem);
}
