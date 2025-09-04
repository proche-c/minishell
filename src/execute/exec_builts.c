/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builts.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2023/09/30 19:46:24 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec_builtins(t_master *master, t_data	*list, int fd)
{
	if (ft_strncmp(list->cmd, "cd", 3) == 0)
		ft_is_cd(master, list);
	else if (ft_compare_upper_lower(list->cmd, "echo") == 1)
		ft_echo(list, fd);
	else if (ft_strncmp(list->cmd, "export", 7) == 0)
		ft_is_export(master, list, fd);
	else if (ft_compare_upper_lower(list->cmd, "env") == 1)
		ft_is_env(master, list, fd);
	else if (ft_strncmp(list->cmd, "unset", 6) == 0)
		ft_is_unset(master, list);
	else if (ft_compare_upper_lower(list->cmd, "pwd") == 1)
		ft_pwd(master);
	else if (ft_strncmp(list->cmd, "exit", 5) == 0)
		ft_exit(master, list);
	if (master->num_pipes > 0)
		exit(0);
}

void	ft_prev_execute_builtins(t_master *master, t_data *list)
{
	if (master->fd_redir != 0)
	{
		if (master->redir_type == 2 || master->redir_type == 4)
			ft_exec_builtins(master, list, master->fd_redir);
	}
	else if (master->num_pipes != 0)
	{
		ft_exec_builtins(master, list,
			master->pipes[master->executed_pipes + 1][WRITE]);
	}
	else
		ft_exec_builtins(master, list, 1);
}
