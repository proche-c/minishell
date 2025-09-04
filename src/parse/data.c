/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42barcelona.    +#+  +:+       +#+        */
/*   By: proche-c <proche-c@student.42barcelona.  +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2023/07/02 20:23:47 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_is_builtins(t_data *new_data)
{
	while (new_data != NULL)
	{
		if (ft_strncmp(new_data->cmd, "echo", 5) == 0
			|| ft_strncmp(new_data->cmd, "cd", 3) == 0
			|| ft_strncmp(new_data->cmd, "pwd", 4) == 0
			|| ft_strncmp(new_data->cmd, "export", 7) == 0
			|| ft_strncmp(new_data->cmd, "unset", 6) == 0
			|| ft_strncmp(new_data->cmd, "exit", 5) == 0
			|| ft_is_an_env(new_data) == 0
			|| ft_strncmp(new_data->cmd, "Echo", 5) == 0
			|| ft_strncmp(new_data->cmd, "eCho", 5) == 0
			|| ft_strncmp(new_data->cmd, "ecHo", 5) == 0
			|| ft_strncmp(new_data->cmd, "echO", 5) == 0
			|| ft_strncmp(new_data->cmd, "EchO", 5) == 0
			|| ft_strncmp(new_data->cmd, "eCHo", 5) == 0
			|| ft_strncmp(new_data->cmd, "EcHo", 5) == 0
			|| ft_strncmp(new_data->cmd, "eChO", 5) == 0)
		{
			new_data->type = BUILTIN;
		}
		new_data = new_data->next;
	}
}

int	ft_is_an_env(t_data *new_data)
{
	if (ft_strncmp(new_data->cmd, "env", 4) == 0
		|| ft_strncmp(new_data->cmd, "Env", 4) == 0
		|| ft_strncmp(new_data->cmd, "eNv", 4) == 0
		|| ft_strncmp(new_data->cmd, "enV", 4) == 0
		|| ft_strncmp(new_data->cmd, "ENv", 4) == 0
		|| ft_strncmp(new_data->cmd, "EnV", 4) == 0
		|| ft_strncmp(new_data->cmd, "eNV", 4) == 0
		|| ft_strncmp(new_data->cmd, "ENV", 4) == 0)
	{
		return (0);
	}
	return (1);
}

t_data	*ft_get_data(t_master *master, t_data *new_data, int j)
{
	if (!master->elem[j] || ft_strlen(&master->elem[j][0]) == 0)
		return (NULL);
	if (master->elem[j][0] == '|')
	{
		new_data->type = PIPE;
		master->num_pipes++;
		free(master->elem[j]);
	}
	else if (master->elem[j][0] == '>' || master->elem[j][0] == '<')
		new_data = ft_get_redir(master, new_data, j);
	else
		new_data = ft_get_cmds(master, new_data, j);
	return (new_data);
}

t_data	*ft_get_redir(t_master *master, t_data *new_data, int j)
{
	if (master->elem[j][0] == '>')
	{
		if (master->elem[j][1] && master->elem[j][1] == '>')
			new_data->type = DFILE_OUT;
		else
			new_data->type = FILE_OUT;
		master->num_redir++;
	}
	else if (master->elem[j][0] == '<')
	{
		if (master->elem[j][1] && master->elem[j][1] == '<')
			new_data->type = DFILE_IN;
		else
			new_data->type = FILE_IN;
		master->num_redir++;
	}
	free(master->elem[j]);
	return (new_data);
}
