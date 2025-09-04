/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2023/09/30 19:46:19 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_data	*ft_small_execute_else(t_data *list)
{
	if (!list)
		return (list);
	if (list != NULL)
	{
		if (list->next && list->next->type == PIPE)
			list = list->next->next;
	}
	return (list);
}

static t_data	*ft_while(t_master *master, t_data *list)
{
	while (list)
	{
		if (list->type == PIPE)
		{
			master->executed_pipes++;
			list = list->next;
			break ;
		}
		list = list->next;
	}
	return (list);
}

t_data	*ft_small_execute(t_master *master, t_data *list)
{
	if ((list->type == 0 && list->cmd
			&& master->execute == 1 && master->error == 0)
		|| (list->type == BUILTIN && list->cmd
			&& master->execute == 1 && master->error == 0))
	{
		ft_prev_execute_cmds(master, list);
		if (master->num_pipes != 0)
			list = ft_while(master, list);
		else
			list = list->next;
		master->executed_cmds++;
		if (master->priority_g_return != -42)
		{
			g_returnvalue = master->priority_g_return;
			master->priority_g_return = -42;
		}
	}
	else
		return (ft_small_execute_else(list));
	return (list);
}

void	ft_big_execute(t_master *master)
{
	t_data	*list;

	list = master->list;
	ft_pre_while(master, list);
	list = master->list;
	while (list && master->executed_cmds < master->num_cmds
		&& master->error == 0)
	{
		list = ft_check_pre_execute(master, list);
		if (!list)
			break ;
		list = ft_small_execute(master, list);
	}
}
