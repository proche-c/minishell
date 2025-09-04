/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veaz <veaz@student.42.fr>                  +#+  +:+       +#+        */
/*   By: proche-c <proche-c@student.42barcelona.  +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2023/06/03 21:58:24 by veaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_parse_dollar(t_master *master, char *strmaster, int i, t_quo *ini)
{
	char	*aux;
	int		j;

	aux = NULL;
	while (strmaster[i] != '\0' && master->error == 0 && strmaster != NULL)
	{
		if (strmaster[i] == '$' && ft_find_quote_rev(strmaster, i) % 2 == 0)
		{
			j = i;
			i = i + ft_get_new_pos(master, strmaster, i);
			aux = ft_strdup(strmaster);
			free(strmaster);
			strmaster = ft_get_new_master(master, aux, j, ini);
		}
		if (strmaster[0] == '\0' || strmaster == NULL
			|| ft_blank(strmaster) == 1)
			break ;
		else
			i++;
	}
	return (strmaster);
}

char	*ft_get_new_master(t_master *master, char *aux, int i, t_quo *ini)
{
	char	*value;
	char	*new_str;
	int		caso;
	t_quo	*auxq;

	value = NULL;
	auxq = NULL;
	value = ft_get_val(aux, i, master, ft_len_var(aux, i));
	caso = ft_get_caso(aux, i, value);
	new_str = ft_replace_dollar(master, aux, i, caso);
	if (caso == 4)
		ft_eval_quotes_value(value, i, ini, auxq);
	if (value != NULL)
		free(value);
	return (new_str);
}

char	*ft_replace_dollar(t_master *master, char *aux, int i, int caso)
{
	char	*aux2;

	aux2 = NULL;
	if (caso == 0)
	{
		aux2 = ft_strdup(aux);
		free(aux);
	}
	else if (caso == 1)
		aux2 = ft_replace_dollar_1(master, aux, i);
	else if (caso == 2)
		aux2 = ft_replace_dollar_2(master, aux, i);
	else if (caso == 3)
		aux2 = ft_replace_dollar_3(master, aux, i);
	else if (caso == 5 || caso == 4)
		aux2 = ft_replace_dollar_4(master, aux, i);
	return (aux2);
}

char	*ft_get_esp_var(char *aux, int i, t_master *master)
{
	char	*value;

	value = NULL;
	value = malloc(sizeof(char) * 2);
	if (!value)
		master->error = 1;
	else
	{
		if (aux[i + 3] == 'n')
			value[0] = '\n';
		else if (aux[i + 3] == 't')
			value[0] = '\t';
		else if (aux[i + 3] == 'r')
			value[0] = '\r';
		value[1] = '\0';
	}
	return (value);
}

int	ft_esp_var(char *str, int j)
{
	int	len;

	len = 0;
	while (str[j] != '\0')
	{
		j++;
		len++;
	}
	j = j - len;
	if (len > 4 && str[j + 1] == '\'' && str[j + 2] == '\\'
		&& str[j + 4] == '\'' && (str[j + 3] == 'n'
			|| str[j + 3] == 't' || str[j + 3] == 'r'))
		return (1);
	else
		return (0);
}
