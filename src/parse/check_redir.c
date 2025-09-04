/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42barcelona.    +#+  +:+       +#+        */
/*   By: proche-c <proche-c@student.42barcelona.  +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2023/07/08 20:20:47 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_check_re_pipes(t_master *master)
{
	ft_check_double_re_pipe(master, '>');
	if (master->error == 0)
		ft_check_double_re_pipe(master, '<');
	if (master->error == 0)
		ft_check_single_re_pipe(master, '>');
	if (master->error == 0)
		ft_check_single_re_pipe(master, '<');
}

int	ft_check_redir_end(t_master *master)
{
	t_data	*temp;
	t_data	*prev;

	temp = master->list;
	while (temp->next)
	{
		if (temp->next->next == NULL)
			prev = temp;
		temp = temp->next;
	}
	if (temp->type >= 2 && temp->type <= 5)
	{
		if (prev->type == 2 && temp->type == 3)
			return (2);
		return (1);
	}
	return (0);
}

int	ft_check_double_redir(t_master *master)
{
	t_data	*temp;

	temp = master->list;
	while (temp)
	{
		if (temp->type >= 2 && temp->type <= 5)
		{
			if (temp->next->type >= 2 && temp->next->type <= 5)
				return (temp->next->type);
		}
		temp = temp->next;
	}
	return (0);
}
