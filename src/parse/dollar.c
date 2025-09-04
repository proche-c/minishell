/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veaz <veaz@student.42.fr>                  +#+  +:+       +#+        */
/*   By: proche-c <proche-c@student.42barcelona.  +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2023/06/03 21:58:24 by veaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_replace_dollar_1(t_master *master, char *aux, int i)
{
	char	*result;
	char	*rest;
	char	*start;
	char	*value;

	result = NULL;
	rest = NULL;
	start = NULL;
	value = NULL;
	value = ft_itoa(g_returnvalue);
	start = ft_substr(aux, 0, i);
	rest = ft_substr(aux, i + 2, ft_strlen(aux) - i - 2);
	result = ft_strjoin_3(start, value, rest, master);
	free(aux);
	free(start);
	free(rest);
	free(value);
	return (result);
}

char	*ft_replace_dollar_2(t_master *master, char *aux, int i)
{
	char	*result;
	char	*value;
	char	*rest;
	char	*start;
	char	*val;

	result = NULL;
	val = ft_get_esp_var(aux, i, master);
	value = ft_strjoin_3("\"", val, "\"", master);
	if (master->error == 0)
	{
		start = ft_substr(aux, 0, i);
		rest = ft_substr(aux, i + 5, ft_strlen(aux) - i - 5);
		result = ft_strjoin_3(start, value, rest, master);
		free(start);
		free(rest);
		free(aux);
		free(value);
		free(val);
	}
	return (result);
}

char	*ft_replace_dollar_3(t_master *master, char *aux, int i)
{
	char	*result;
	char	*rest;
	char	*start;
	char	*value;
	int		len_var;

	result = NULL;
	value = NULL;
	start = NULL;
	rest = NULL;
	len_var = ft_len_var(aux, i);
	start = ft_substr(aux, 0, i);
	rest = ft_substr(aux, i + len_var + 1, ft_strlen(aux) - i - len_var - 1);
	result = ft_strjoin_3(start, value, rest, master);
	free(start);
	free(rest);
	free(value);
	free(aux);
	return (result);
}

char	*ft_replace_dollar_4(t_master *master, char *aux, int i)
{
	char	*result;
	char	*rest;
	char	*start;
	char	*value;
	int		len;

	result = NULL;
	rest = NULL;
	start = NULL;
	value = NULL;
	value = ft_get_val(aux, i, master, ft_len_var(aux, i));
	if (!value)
		master->error = 1;
	else
	{
		start = ft_substr(aux, 0, i);
		len = ft_strlen(aux) - i - ft_len_var(aux, i) - 1;
		rest = ft_substr(aux, i + ft_len_var(aux, i) + 1, len);
		result = ft_strjoin_3(start, value, rest, master);
		free(start);
		free(rest);
		free(aux);
		free(value);
	}
	return (result);
}
