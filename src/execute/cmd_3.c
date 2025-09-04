/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2023/08/20 22:09:58 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_cmd_3_with_fd(t_master *master, t_data *list)
{
	if (master->redir_type == 2 || master->redir_type == 4)
		ft_cmd_redir_output(master, list);
	else if (master->redir_type == 3)
		ft_cmd_redir_input(master, list);
}

void	ft_cmd_3(t_master *master, t_data *list)
{
	if (master->fd_redir != 0)
		ft_cmd_3_with_fd(master, list);
	else
	{
		if (master->num_pipes == 1 && master->executed_pipes == -1)
			master->executed_pipes = 0;
		if (master->num_pipes > 0 && master->executed_pipes < master->num_pipes)
		{
			dup2(master->pipes[master->executed_pipes][READ], STDIN_FILENO);
			dup2(STDIN_FILENO, master->pipes[master->executed_pipes][READ]);
			close(master->pipes[master->executed_pipes][READ]);
		}
		if (list->type == BUILTIN)
			ft_exec_builtins(master, list, 1);
		else
			ft_execute_cmd_real(master, list);
	}
}
