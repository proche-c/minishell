/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42barcelona.    +#+  +:+       +#+        */
/*   By: proche-c <proche-c@student.42barcelona.  +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2023/08/20 23:22:13 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_words_after_redir(t_data *list)
{
	t_data	*temp;
	t_down	*temp_down;
	int		x;

	temp = list;
	temp_down = NULL;
	x = 0;
	while ((temp && temp->type < PIPE && temp->type > BUILTIN)
		|| (temp && !temp->type))
	{
		if (temp->down)
		{
			temp_down = temp->down;
			while (temp_down)
			{
				temp_down = temp_down->next;
				x++;
			}
		}
		x++;
		temp = temp->next;
	}
	return (x);
}

int	ft_redirections_until_next_pipe(t_master *master, t_data *list)
{
	int	num[3];

	num[0] = 0;
	num[1] = 0;
	num[2] = 0;
	while (list && list->type != PIPE)
	{
		if (list->type == 2)
			num[0]++;
		if (list->type == 3)
			num[1]++;
		if (list->type == 4)
			num[2]++;
		list = list->next;
	}
	if (master->num_redir == num[0])
		return (num[0]);
	if (master->num_redir == num[1])
		return (num[1]);
	if (master->num_redir == num[2])
		return (num[2]);
	else if ((num[0] + num[1] + num[2]) > 1)
		return (num[0] + num[1] + num[2]);
	return (0);
}

void	ft_delete_redir(t_master *master, t_data *list)
{
	t_data	*temp;
	int		to_delete;
	int		fd;

	temp = list;
	fd = ft_redirections_until_next_pipe(master, list);
	to_delete = (fd - 1) * 2;
	ft_check_args_re(master);
	if (master->execute == FALSE)
		return ;
	else
	{
		while (temp->next && list->next->type != PIPE && to_delete > 0)
		{
			if (temp->type == 2 || temp->type == 4 || temp->type == 3)
				ft_pre_create_file(master, temp);
			else if (temp->next->type == 2
				|| temp->next->type == 4 || temp->next->type == 3)
				ft_pre_create_file(master, temp->next);
			if (list->next->type == 2)
				master->num_redir--;
			ft_delete_next_node_data(list);
			to_delete--;
		}
	}
}
