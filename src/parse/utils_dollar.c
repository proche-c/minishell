/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veaz <veaz@student.42.fr>                  +#+  +:+       +#+        */
/*   By: proche-c <proche-c@student.42barcelona.  +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2023/06/03 21:58:24 by veaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_with_dollar(char *strmaster)
{
	int	i;
	int	quote;
	int	dquote;

	i = 0;
	quote = 0;
	dquote = 0;
	while (strmaster[i] != '\0')
	{
		if (strmaster[i] == '\'' && dquote % 2 == 0)
			quote++;
		else if (strmaster[i] == '"' && quote % 2 == 0)
			dquote++;
		else if (strmaster[i] == '$'
			&& ft_find_quote(strmaster, 1, i - 1) % 2 == 0)
			return (1);
		i++;
	}
	return (0);
}

int	ft_get_caso(char *aux, int i, char *value)
{
	int		len_value;
	int		len_var;

	len_var = ft_len_var(aux, i);
	len_value = 0;
	if (value != NULL)
		len_value = ft_strlen(value);
	if (aux[i + 1] == '\'' && ft_esp_var(aux, i) == 1)
		return (2);
	else if (len_var == 0)
		return (0);
	else if (aux[i + 1] == '?')
		return (1);
	else if (len_value == 0)
		return (3);
	else if (aux[i + 1] == '\'' || aux[i + 1] == '"')
		return (5);
	else
		return (4);
}

int	ft_get_len_itoa(void)
{
	int		result;
	char	*str;

	str = ft_itoa(g_returnvalue);
	result = ft_strlen(str);
	free(str);
	return (result);
}

int	ft_get_new_pos(t_master *master, char *str, int i)
{
	int		len_value;
	int		caso;
	char	*value;

	value = NULL;
	value = ft_get_val(str, i, master, ft_len_var(str, i));
	caso = ft_get_caso(str, i, value);
	len_value = 0;
	if (value != NULL)
	{
		len_value = ft_strlen(value);
		free (value);
	}
	if (caso == 0 || caso == 2)
		return (0);
	else if (caso == 1)
		return (ft_get_len_itoa() - 1);
	else if (caso == 3)
		return (-1);
	else if (caso == 4)
	{
		return (len_value - 1);
	}
	else
		return (-100);
}

int	ft_blank(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isspace(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}
