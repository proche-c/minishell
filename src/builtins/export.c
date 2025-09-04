/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2023/09/30 19:22:23 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_is_export(t_master *master, t_data *list, int fd)
{
	t_down	*temp;

	if (list->num_args > 0)
	{
		temp = list->down;
		while (temp != NULL)
		{
			ft_export_with_var(master, temp->arg);
			temp = temp->next;
		}
	}
	else
		ft_export(master->envp, fd);
}

void	ft_add_var_envp(t_envp *envp, char *str, char *key, char *value)
{
	t_envp	*newenvp;
	t_envp	*last;
	char	*aux;

	newenvp = ft_new_envp(key, value);
	if (ft_has_equal(str) == 1)
	{
		aux = ft_get_value(str);
		if (aux != NULL)
		{
			newenvp->type = 1;
			free(aux);
		}
		else
			newenvp->type = 2;
	}
	else
		newenvp->type = 3;
	last = ft_lst_last(envp);
	last->next = newenvp;
}

void	ft_replace_var_envp(t_envp *envp, char *key, char *value)
{
	char	*aux;

	while (envp != NULL)
	{
		aux = ft_get_key(envp->key);
		if (ft_strncmp(key, aux, (ft_strlen(key) + 1)) == 0)
		{
			if (value)
			{
				if (envp->value)
					free(envp->value);
				envp->value = ft_strdup(value);
			}
		}
		envp = envp->next;
		free(aux);
	}
}

void	ft_export_with_var(t_master *master, char *arg)
{
	char	*key;
	char	*temp;

	temp = NULL;
	key = ft_get_key(arg);
	if (ft_check_first_value(key, arg) == 1)
	{
		free(key);
		return ;
	}
	if (key[ft_strlen(key) - 1] == '+')
	{
		if (ft_export_aux(master, temp, key, arg) == 1)
			return ;
	}
	ft_export_with_var_normal_case(master, key, arg);
	ft_update_envp(master);
	free(key);
	g_returnvalue = 0;
}

void	ft_export(t_envp *envp, int fd)
{
	t_envp	*temp;
	char	*aux;

	aux = NULL;
	temp = envp;
	while (temp != NULL)
	{
		ft_putstr_fd("declare -x ", fd);
		ft_temp_type(temp, aux, fd);
		temp = temp->next;
	}
	g_returnvalue = 0;
}
