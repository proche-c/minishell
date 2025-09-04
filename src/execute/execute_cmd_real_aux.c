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

void	ft_handle_no_path(t_master *master)
{
	if (ft_is_in_envp(master->envp, "PATH") == 0)
		exit(127);
}

void	ft_execute_dot_path(t_master *master, t_data *list)
{
	char	*str;

	if (list->cmd[0] == '.' && list->cmd[1] == '/')
	{
		str = &list->cmd[2];
		str = ft_strjoin(ft_my_path(), "/");
		str = ft_strjoin(str, &list->cmd[2]);
		if (execve(str, list->args, master->env) == -1)
			exit(126);
	}
}

void	ft_execute_from_bin_paths(t_master *master, t_data *list)
{
	int	y;

	y = 0;
	ft_get_paths_vesionvictor(master, list);
	while (master->bin_paths[y])
	{
		if (access(master->bin_paths[y], F_OK) == 0)
		{
			if (execve(master->bin_paths[y], list->args, master->env) == -1)
				exit(126);
		}
		y++;
	}
}

void	ft_execute_relative_path(t_master *master, t_data *list)
{
	ft_handle_no_path(master);
	ft_execute_dot_path(master, list);
	ft_execute_from_bin_paths(master, list);
}
