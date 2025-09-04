/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2023/08/20 23:13:29 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_cmd_1_redir_input_with_pipe(t_master *master, t_data *list)
{
	dup2(master->fd_redir, STDIN_FILENO);
	dup2(master->pipes[0][WRITE], STDOUT_FILENO);
	if (list->type == BUILTIN)
		ft_exec_builtins(master, list, 1);
	else
		ft_execute_cmd_real(master, list);
	close(master->fd_redir);
	master->fd_redir = 0;
}

static void	ft_cmd_1_with_fd(t_master *master, t_data *list)
{
	if (master->num_pipes == 0)
	{
		if (master->redir_type == 2 || master->redir_type == 4)
			ft_cmd_redir_output(master, list);
		else if (master->redir_type == 3)
			ft_cmd_redir_input(master, list);
		return ;
	}
	else
	{
		if (master->redir_type == 2 || master->redir_type == 4)
			ft_cmd_redir_output(master, list);
		else if (master->redir_type == 3)
			ft_cmd_1_redir_input_with_pipe(master, list);
		return ;
	}
}

static void	ft_cmd_1_with_pipe(t_master *master, t_data *list)
{
	close(master->pipes[0][READ]);
	dup2(master->pipes[0][WRITE], STDOUT_FILENO);
	if (list->type == BUILTIN)
		ft_exec_builtins(master, list, 1);
	else
		ft_execute_cmd_real(master, list);
	close(master->pipes[0][WRITE]);
}

void	ft_cmd_1(t_master *master, t_data *list)
{
	if (master->fd_redir != 0)
		ft_cmd_1_with_fd(master, list);
	else if (master->num_pipes != 0)
		ft_cmd_1_with_pipe(master, list);
	else
	{
		if (list->type == BUILTIN)
			ft_exec_builtins(master, list, 1);
		else
			ft_execute_cmd_real(master, list);
	}
}
