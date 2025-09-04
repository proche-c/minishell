/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2023/09/30 18:11:19 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_is_env(t_master *master, t_data *list, int fd)
{
	if (list->num_args == 0)
		ft_env(master->envp, fd);
	else
		ft_return_error_3("env: ",
			list->down->arg, ": No such file or directory\n");
}

int	ft_is_in_envp(t_envp *envp, char *str)
{
	int		len;
	char	*key;

	len = ft_strlen(str);
	while (envp != NULL)
	{
		key = ft_get_key(envp->key);
		if (ft_strncmp(str, key, len + 1) == 0)
		{
			free(key);
			return (1);
		}
		free(key);
		envp = envp->next;
	}
	return (0);
}

char	*ft_get_value_envp(t_master *master, char	*key)
{
	t_envp	*temp;

	temp = master->envp;
	while (temp)
	{
		if (ft_strncmp(temp->key, key, ft_strlen(temp->key) + 1) == 0)
			return (temp->value);
		temp = temp->next;
	}
	return (NULL);
}

void	ft_export_with_var_aux(t_master *master, char *key, char *arg)
{
	char	*value;
	char	*temp;

	temp = NULL;
	value = ft_get_value_export(master, key);
	temp = ft_get_value(arg);
	value = ft_strjoin(value, temp);
	ft_replace_var_envp(master->envp, key, value);
	ft_update_envp(master);
	free(temp);
	free(value);
	g_returnvalue = 0;
}

void	ft_export_with_var_normal_case(t_master *master, char *key, char *arg)
{
	char	*value;

	value = ft_get_value(arg);
	if (ft_is_in_envp(master->envp, key) == 1)
		ft_replace_var_envp(master->envp, key, value);
	else
		ft_add_var_envp(master->envp, arg, key, value);
	free(value);
}
