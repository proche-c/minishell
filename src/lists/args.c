/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42barcelona.    +#+  +:+       +#+        */
/*   By: proche-c <proche-c@student.42barcelona.  +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2023/08/20 23:22:13 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_add_arg(t_down *next_down, t_data *next, t_data *start)
{
	next_down = next->next->down;
	if (start->num_args == 0)
	{
		start->down = next_down;
		start->num_args++;
	}
	else
	{
		start->num_args = next->next->num_args + start->num_args;
		start->down->next = next_down;
	}
}

void	ft_recount_args(t_data *temp, t_data *next, t_data *start)
{
	t_down	*temp_down;
	t_down	*next_down;

	next_down = NULL;
	if (next->next->num_args > 0)
	{
		temp_down = temp->down;
		if (temp_down)
		{
			while (temp_down->next != NULL)
			{
				temp_down = temp_down->next;
			}
			next_down = next->next->down;
			temp_down->next = next_down;
		}
		else
			ft_add_arg(next_down, next, start);
		next->next->down = NULL;
		next->next->num_args = 0;
	}
}

void	ft_add_down(t_master *master, t_data *temp, t_down *down, int pipes)
{
	t_data	*new;

	down = temp->next->down;
	new = ft_new_cmd(master);
	new->cmd = down->arg;
	new->num_args = temp->next->num_args - 1;
	if (new->num_args > 0)
	{
		new->down = temp->next->down->next;
		temp->next->down = NULL;
		temp->next->num_args = 0;
		new->next = temp;
		temp = new;
		temp->type = 0;
		if (pipes == 0)
		{
			master->list = temp;
			master->list->type = 0;
		}
	}
}

int	ft_how_many_args(t_master *master, t_data *list)
{
	t_data	*temp;
	t_down	*down;
	int		pipes;

	temp = list;
	down = NULL;
	pipes = 0;
	while (temp && temp->type != PIPE)
	{
		if (temp->type == 2 || temp->type == 4)
		{
			if (temp->next)
			{
				if (temp->next->num_args > 0)
				{
					ft_add_down(master, temp, down, pipes);
				}
			}
		}
		if (temp->type == PIPE)
			pipes++;
		temp = temp->next;
	}
	return (0);
}

void	ft_fix_args(t_master *master, t_data *list)
{
	t_data	*start;
	t_data	*temp;
	t_data	*next;
	int		res;

	start = list;
	temp = list;
	next = list->next;
	res = ft_redirections_until_next_pipe(master, list);
	if (res > 0)
	{
		ft_delete_redir(master, list);
		ft_how_many_args(master, list);
		list = master->list;
	}
	next = list->next;
	while (temp != NULL && next != NULL)
	{
		if (next && next->type >= 2 && next->type <= 5)
			ft_recount_args(temp, next, start);
		temp = next;
		next = next->next;
	}
	return ;
}
