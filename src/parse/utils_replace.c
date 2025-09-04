/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_replace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veaz <veaz@student.42.fr>                  +#+  +:+       +#+        */
/*   By: proche-c <proche-c@student.42barcelona.  +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2023/06/03 21:58:24 by veaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_val(char *aux, int i, t_master *master, int len_var)
{
	char	*value;

	value = NULL;
	if (len_var > 0)
	{
		if (aux[i + 1] == '\'' && ft_esp_var(aux, i) == 1)
			value = ft_get_esp_var(aux, i, master);
		else if (aux[i + 1] == '\'' || aux[i + 1] == '"')
			value = ft_get_val_1(aux, i, master, len_var);
		else
			value = ft_get_val_2(aux, i, master, len_var);
	}
	return (value);
}

char	*ft_get_val_1(char *aux, int i, t_master *master, int len_var)
{
	char	*value;
	int		k;

	value = NULL;
	value = malloc(sizeof(char) * (len_var + 1));
	if (value)
	{
		i++;
		k = 0;
		while (k < len_var)
		{
			value[k++] = aux[i++];
		}
		value[k++] = '\0';
	}
	else
		master->error = 1;
	return (value);
}

char	*ft_get_val_2(char *aux, int i, t_master *master, int len_var)
{
	char	*var;
	char	*value;
	t_envp	*iter;

	value = NULL;
	var = ft_get_var(aux, i, master, len_var);
	if (master->error == 0)
	{
		iter = master->envp;
		while (iter != NULL)
		{
			if (ft_strncmp(var, iter->key, ft_strlen(iter->key) + 1) == 0)
			{
				if (iter->value != NULL)
					value = ft_strdup(iter->value);
				iter = master->envp;
				free(var);
				return (value);
			}
			iter = iter->next;
		}
		iter = master->envp;
		free(var);
	}
	return (value);
}

char	*ft_get_var(char *aux, int i, t_master *master, int len_var)
{
	char	*var;
	int		k;

	i++;
	var = NULL;
	var = (char *)malloc(sizeof(char) * (len_var + 1));
	if (!var)
		master->error = 1;
	else
	{
		k = 0;
		while (k < len_var)
			var[k++] = aux[i++];
		var[k] = '\0';
	}
	return (var);
}
