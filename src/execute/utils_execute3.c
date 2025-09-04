/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_execute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2023/08/20 23:33:16 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_handle_single_builtin(t_master *master, t_data *list)
{
	if (master->num_pipes > 0)
		ft_cmd_1(master, list);
	else if (master->fd_redir != 0)
	{
		if (master->redir_type == 2 || master->redir_type == 4)
			ft_exec_builtins(master, list, master->fd_redir);
		else if (master->redir_type == 3)
			ft_exec_builtins(master, list, 1);
	}
	else
		ft_exec_builtins(master, list, 1);
}

void	ft_handle_first_cmd(t_master *master, t_data *list, int *pid)
{
	*pid = fork();
	if (*pid == 0)
		ft_cmd_1(master, list);
	else
	{
		if (master->num_pipes != 0)
			close(master->pipes[0][WRITE]);
	}
}

void	ft_handle_last_cmd(t_master *master, t_data *list, int *pid)
{
	*pid = fork();
	if (*pid == 0)
		ft_cmd_3(master, list);
	else
		close(master->pipes[0][READ]);
}

void	ft_handle_middle_cmd(t_master *master, t_data *list, int *pid)
{
	*pid = fork();
	if (*pid == 0)
		ft_cmd_2(master, list);
	else
	{
		close(master->pipes[master->executed_pipes][READ]);
		close(master->pipes[master->executed_pipes + 1][WRITE]);
	}
}

void	ft_handle_return_values(int status_waitpid, t_data *list)
{
	g_returnvalue = WEXITSTATUS(status_waitpid);
	if (g_returnvalue == 127)
	{
		ft_return_error(list->cmd, ": command not found\n");
		g_returnvalue = 127;
	}
	else if (g_returnvalue == 126)
		printf("%s: Permission denied\n", list->cmd);
	else if (g_returnvalue == 130)
	{
		ft_return_error(list->cmd, ": No such file or directory\n");
		g_returnvalue = 127;
	}
	if (WIFSIGNALED(status_waitpid))
	{
		if (WTERMSIG(status_waitpid) == 2)
			g_returnvalue = 130;
		else if (WTERMSIG(status_waitpid) == 3)
			g_returnvalue = 131;
	}
}
