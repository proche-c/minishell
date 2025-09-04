/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2023/09/30 18:39:37 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_clean_pipes(t_master *master)
{
	int	x;

	x = 0;
	if (master->pipes)
	{
		x = 0;
		while (x < master->num_pipes)
		{
			free(master->pipes[x]);
			x++;
		}
		free(master->pipes);
	}
}

void	ft_clean_elem_char(t_master *master)
{
	if (master->elem)
	{
		free(master->elem);
		master->elem = NULL;
	}
}

void	ft_clean_master_middle(t_master *master)
{
	if (ft_spaces(master->str) == 1)
		return ;
	ft_clean_list(master);
	if (master->str)
	{
		free(master->str);
		master->str = NULL;
	}
	ft_clean_elem_char(master);
	ft_clean_pipes(master);
}

void	ft_clean_master_all(t_master *master)
{
	ft_clean_list(master);
	ft_clean_envp(master);
	if (master->str)
	{
		free(master->str);
		master->str = NULL;
	}
	ft_clean_elem_char(master);
	ft_clean_pipes(master);
	if (master->home)
		free(master->home);
}

void	ft_clean_env_char(t_master *master)
{
	int	x;

	x = 0;
	if (!master->env)
		return ;
	while (master->env[x])
	{
		free(master->env[x]);
		x++;
	}
	free(master->env);
	master->env = NULL;
}
