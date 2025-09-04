/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_lists.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2023/09/30 13:00:42 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_clean_envp_node(t_envp *envp)
{
	if (envp->key)
		free(envp->key);
	if (envp->value)
		free(envp->value);
}

void	ft_clean_env(t_master *master)
{
	int	x;

	x = 0;
	while (master->env[x])
	{
		x++;
	}
}

void	ft_clean_envp(t_master *master)
{
	t_envp	*list;
	t_envp	*next;

	list = master->envp;
	if (list->next)
		next = list->next;
	else
		next = NULL;
	while (list)
	{
		ft_clean_envp_node(list);
		if (next)
		{
			list = next;
		}
		else
		{
			list = NULL;
		}
		if (list && list->next)
			next = list->next;
		else
			next = NULL;
	}
}
