/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entry.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42barcelona.    +#+  +:+       +#+        */
/*   By: proche-c <proche-c@student.42barcelona.  +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2023/08/16 21:00:24 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_get_value_list(t_master *master)
{
	t_data	*newlist;
	t_data	*temp;
	int		x;

	x = 1;
	master->list = ft_new_cmd(master);
	if (master->list)
	{
		master->list = ft_get_data(master, master->list, 0);
		if (master->error == 0 && master->list)
		{
			temp = master->list;
			while (x < master->num_elem && master->error == 0)
			{
				newlist = ft_new_cmd(master);
				newlist = ft_get_data(master, newlist, x);
				if (newlist != NULL)
				{
					temp->next = newlist;
					temp = temp->next;
				}
				x++;
			}
		}
	}
}

void	ft_get_entry(t_master *master)
{
	ft_separate_str(master);
	if (master->elem != NULL && master->error == 0)
	{
		ft_get_value_list(master);
	}
}
