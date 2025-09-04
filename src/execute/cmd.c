/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2023/08/20 22:10:26 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cmd_redir_output(t_master *master, t_data *list)
{
	dup2(master->fd_redir, STDOUT_FILENO);
	master->fd_redir = 0;
	close(master->fd_redir);
	if (list->type == BUILTIN)
		ft_exec_builtins(master, list, 1);
	else
		ft_execute_cmd_real(master, list);
}

void	ft_cmd_redir_input(t_master *master, t_data *list)
{
	dup2(master->fd_redir, STDIN_FILENO);
	if (list->type == BUILTIN)
		ft_exec_builtins(master, list, 1);
	else
		ft_execute_cmd_real(master, list);
	close(master->fd_redir);
	master->fd_redir = 0;
}
