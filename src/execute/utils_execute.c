/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_execute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2023/09/30 19:10:28 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_prev_execute_cmds(t_master *master, t_data *list)
{
	int	status_waitpid;
	int	pid;

	status_waitpid = 666;
	pid = 0;
	if (master->executed_cmds == 0)
	{
		if (master->num_cmds == 1 && list->type == BUILTIN)
		{
			ft_handle_single_builtin(master, list);
			return ;
		}
		ft_handle_first_cmd(master, list, &pid);
	}
	else if (master->executed_cmds == (master->num_cmds - 1))
		ft_handle_last_cmd(master, list, &pid);
	else
		ft_handle_middle_cmd(master, list, &pid);
	if (master->fd_redir != 0)
	{
		close(master->fd_redir);
		master->fd_redir = 0;
	}
	waitpid(pid, &status_waitpid, 0);
	ft_handle_return_values(status_waitpid, list);
}

void	ft_to_execute(t_master *master, t_data *list)
{
	if (list->type == BUILTIN)
		ft_prev_execute_builtins(master, list);
	else
		ft_prev_execute_cmds(master, list);
}
