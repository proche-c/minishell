/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2023/09/30 19:22:36 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_temp_type(t_envp *temp, char *aux, int fd)
{
	char	*aux2;

	if (temp->type == 1)
	{
		aux = ft_strjoin(temp->key, "=\"");
		aux2 = ft_strjoin(aux, temp->value);
		free(aux);
		aux = ft_strjoin(aux2, "\"\n");
		ft_putstr_fd(aux, fd);
		free(aux2);
	}
	else if (temp->type == 2)
	{
		aux = ft_strjoin(temp->key, "=\"\"\n");
		ft_putstr_fd(aux, fd);
	}
	else if (temp->type == 3)
	{
		aux = ft_strjoin(temp->key, "\n");
		ft_putstr_fd(aux, fd);
	}
	free(aux);
}

int	ft_check_first_value(char *key, char *arg)
{
	char	*aux;
	char	*aux2;

	if ((key[0] >= '0' && key[0] <= '9')
		|| ft_has_char(key, '/') > 0
		|| ft_has_char(key, ' ') > 0
		|| ft_has_char(key, '%') > 0
		|| ft_has_char(key, ':') > 0)
	{
		aux = ft_strjoin("export: `", arg);
		aux2 = ft_strjoin(aux, "': not a valid identifier\n");
		ft_putstr_fd(aux2, 2);
		g_returnvalue = 1;
		free(aux);
		free(aux2);
		return (1);
	}
	else
		return (0);
}

char	*ft_get_value_export(t_master *master, char *key)
{
	t_envp	*temp;

	temp = master->envp;
	while (temp != NULL)
	{
		if (ft_strncmp(temp->key, key, ft_strlen(key) + 1) == 0)
		{
			return (temp->value);
		}
		temp = temp->next;
	}
	return (NULL);
}

int	ft_has_equal(char *str)
{
	int	x;

	x = 0;
	while (str[x] != '\0')
	{
		if (str[x] == '=')
			return (1);
		x++;
	}
	return (0);
}

int	ft_export_aux(t_master *master, char *temp, char *key, char *arg)
{
	temp = ft_substr(key, 0, ft_strlen(key) - 1);
	free(key);
	key = temp;
	if (ft_is_in_envp(master->envp, temp) == TRUE)
	{
		ft_export_with_var_aux(master, key, arg);
		free(key);
		return (1);
	}
	else
		key = temp;
	return (0);
}
