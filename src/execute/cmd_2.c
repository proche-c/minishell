/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2023/08/20 22:09:06 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_cmd_2_with_fd(t_master *master, t_data *list)
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
		return ;
	}
}

void	ft_cmd_2(t_master *master, t_data *list)
{
	if (master->fd_redir != 0)
		ft_cmd_2_with_fd(master, list);
	else
	{
		if (master->num_pipes == 0)
			return ;
		close(master->pipes[master->executed_pipes + 1][READ]);
		dup2(master->pipes[master->executed_pipes][READ], STDIN_FILENO);
		close(master->pipes[master->executed_pipes][READ]);
		dup2(master->pipes[master->executed_pipes + 1][WRITE], STDOUT_FILENO);
		close(master->pipes[master->executed_pipes + 1][WRITE]);
		if (list->type == BUILTIN)
			ft_exec_builtins(master, list, 1);
		else
			ft_execute_cmd_real(master, list);
	}
}
