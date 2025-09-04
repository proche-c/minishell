/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2023/08/20 19:16:47 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_is_unset(t_master *master, t_data *list)
{
	t_down	*temp;

	if (list->num_args > 0)
	{
		temp = list->down;
		while (temp != NULL)
		{
			ft_unset(master, master->envp, temp->arg);
			temp = temp->next;
		}
	}
}

void	ft_unset(t_master *master, t_envp *envp, char *arg)
{
	t_envp	*temp;
	t_envp	*previous;

	temp = envp;
	while (temp != NULL)
	{
		if (ft_strncmp(temp->key, arg, (ft_strlen(temp->key) + 1)) == 0)
		{
			previous->next = temp->next;
			ft_clean_envp_node(temp);
			free(temp);
			break ;
		}
		previous = temp;
		temp = temp->next;
	}
	ft_update_envp(master);
	g_returnvalue = 0;
}
