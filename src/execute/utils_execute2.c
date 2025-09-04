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

static	t_data	*ft_num_cmds_aux(t_data *list)
{
	list = list->next;
	while (list->type == 0)
	{
		list = list->next;
		if (!list)
			break ;
	}
	return (list);
}

void	ft_num_cmds(t_master *master)
{
	t_data	*list;
	int		x;

	x = 0;
	list = master->list;
	while (list)
	{
		if ((x == 0 && list->type == 2) || (x == 0 && list->type == 3)
			|| (x == 0 && list->type == 4) || list->type == 0
			|| list->type == 6)
			x++;
		if (list->type > 1 && list->type < 6)
		{
			list = ft_num_cmds_aux(list);
			if (!list)
				break ;
		}
		if (list->type == PIPE)
		{
			if (list->next && list->next->type == 2)
				x++;
		}
		list = list->next;
	}
	master->num_cmds = x;
}

int	ft_is_absolute_path(char *str)
{
	int	x;

	x = 0;
	while (str[x])
	{
		if (str[x] == '/')
			return (1);
		x++;
	}
	return (0);
}

int	ft_is_directory(char *path)
{
	struct stat	stats;

	stat(path, &stats);
	if (S_ISDIR(stats.st_mode))
		return (1);
	return (0);
}

void	ft_get_paths_vesionvictor(t_master *master, t_data *list)
{
	char	**bin_paths;
	t_envp	*result;
	char	*cmd;
	int		i;

	result = ft_find_path(master);
	bin_paths = ft_split(result->value, ':');
	cmd = ft_strjoin("/", list->cmd);
	i = 0;
	while (bin_paths[i])
	{
		bin_paths[i] = ft_strjoin(bin_paths[i], cmd);
		i++;
	}
	master->bin_paths = bin_paths;
}
