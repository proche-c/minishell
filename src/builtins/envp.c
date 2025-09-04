/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2023/09/30 19:43:15 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_envp *envp, int fd)
{
	while (envp != NULL)
	{
		if (envp->type == 1)
			ft_put_str_3(envp->key, envp->value, TRUE, fd);
		else if (envp->type == 2)
			ft_put_str_2(envp->key, "=", TRUE, fd);
		envp = envp->next;
	}
}

void	ft_type_envp(t_envp	*new_envp, char	*envp, char *value)
{
	if (ft_search_equal(envp) == 1)
	{
		if (value != NULL)
			new_envp->type = 1;
		else
			new_envp->type = 2;
	}
	else
		new_envp->type = 3;
}

void	ft_update_envp_aux(t_master *master)
{
	t_envp	*envp;
	char	**new_envp;
	char	*aux;
	int		x;

	x = 0;
	new_envp = malloc((ft_envpsize(master->envp) + 1) * sizeof(char *));
	envp = master->envp;
	while (x < ft_envpsize(master->envp))
	{
		aux = ft_strjoin(envp->key, "=");
		if (envp->value)
		{
			new_envp[x] = ft_strjoin(aux, envp->value);
			free(aux);
		}
		else
			new_envp[x] = aux;
		x++;
		envp = envp->next;
	}
	new_envp[x] = NULL;
	ft_clean_env_char(master);
	master->env = new_envp;
}

void	ft_update_envp(t_master *master)
{
	ft_update_envp_aux(master);
	ft_clean_env(master);
}
