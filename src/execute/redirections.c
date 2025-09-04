/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2023/08/20 22:40:53 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	ft_try_open(t_master *master, t_data *list, int type)
{
	if (ft_is_directory(list->cmd) == TRUE)
	{
		ft_return_error(list->cmd, ": Is a directory\n");
		master->fd_redir = -1;
		g_returnvalue = 1;
		master->priority_g_return = 1;
	}
	else
	{
		if (type == SIMPLE)
			master->fd_redir = open(list->cmd, O_WRONLY
					| O_CREAT | O_TRUNC, S_IRUSR
					| S_IWUSR | S_IRGRP | S_IROTH);
		else if (type == APPEND)
			master->fd_redir = open(list->cmd, O_WRONLY
					| O_CREAT | O_APPEND, S_IRUSR
					| S_IWUSR | S_IRGRP | S_IROTH);
		if (master->fd_redir == -1)
		{
			ft_return_error(list->cmd, ": Permission denied\n");
			g_returnvalue = 1;
			master->executed_cmds++;
			master->num_cmds--;
		}
	}
}

static t_data	*ft_redir_output_simple(t_master *master, t_data *list)
{
	master->redir_type = 2;
	if (list && !list->cmd && list->type == 2)
	{
		ft_try_open(master, list->next, SIMPLE);
		return (list->next->next);
	}
	else
	{
		ft_try_open(master, list->next->next, SIMPLE);
		if (master->fd_redir != -1)
		{
			ft_delete_next_node_data(list);
			ft_delete_next_node_data(list);
		}
	}
	return (list);
}

static t_data	*ft_redir_output_double(t_master *master, t_data *list)
{
	master->redir_type = 4;
	if (list->type == 4)
	{
		ft_try_open(master, list->next, APPEND);
		return (list->next->next);
	}
	else
	{
		ft_try_open(master, list->next->next, APPEND);
		if (master->fd_redir != -1)
		{
			ft_delete_next_node_data(list);
			ft_delete_next_node_data(list);
		}
	}
	return (list);
}

t_data	*ft_redirections(t_master *master, t_data *list)
{
	if ((list->next && list->next->type == 2)
		|| (list->next && list->type == 2))
		return (ft_redir_output_simple(master, list));
	if ((list->next != NULL && list->next->type == 3)
		|| (list->next && list->type == 3))
		return (ft_redir_input_simple(master, list));
	if ((list->next != NULL && list->next->type == 4)
		|| (list->next && list->type == 4))
		return (ft_redir_output_double(master, list));
	return (list);
}
