/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2023/08/20 23:26:41 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_handle_errors_and_special_cases(t_data *list)
{
	if (ft_strlen(list->cmd) == 0)
	{
		ft_return_error(list->cmd, ": command not found\n");
		exit(127);
	}
	else if (ft_strncmp(list->cmd, "test", 5) == 0)
		exit(1);
	else if (list->cmd[0] == '/' && access(list->cmd, F_OK) != 0)
		exit(130);
	else if (ft_is_directory(list->cmd) == TRUE)
		exit(130);
}

void	ft_execute_absolute_path(t_master *master, t_data *list)
{
	if (ft_is_absolute_path(list->cmd) == 1)
	{
		if (execve(list->cmd, list->args, master->env) == -1)
		{
			perror("Error executing command");
			exit(126);
		}
	}
	else if (list->cmd[0] == '/')
		exit(130);
}

void	ft_execute_cmd_real(t_master *master, t_data *list)
{
	ft_handle_errors_and_special_cases(list);
	ft_execute_absolute_path(master, list);
	ft_execute_relative_path(master, list);
	exit(127);
}
