/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_lists.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2023/09/30 13:00:42 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_clean_down_node(t_down *down)
{
	if (down->arg)
		free(down->arg);
}

void	ft_clean_data_node(t_data *data)
{
	int		x;

	x = 0;
	if (data->cmd)
		free(data->cmd);
	if (data->args)
	{
		if (data->args[x])
		{
			while (data->args[x])
			{
				free(data->args[x]);
				x++;
			}
		}
		free(data->args);
	}
	ft_clean_data_node_2(data);
}

void	ft_clean_data_node_2(t_data *data)
{
	t_down	*aux;
	t_down	*next_to_delete;

	aux = data->down;
	if (aux)
	{
		while (aux)
		{
			next_to_delete = aux->next;
			ft_clean_down_node(aux);
			free(aux);
			if (next_to_delete)
				aux = next_to_delete;
			else
				aux = NULL;
		}
	}
}

void	ft_clean_list(t_master *master)
{
	t_data	*list;
	t_data	*temp;

	list = master->list;
	temp = NULL;
	if (list)
	{
		if (list && list->next)
			temp = list->next;
		while (list)
		{
			ft_clean_data_node(list);
			free(list);
			if (temp)
				list = temp;
			else
				list = NULL;
			if (list && list->next)
				temp = list->next;
			else
				temp = NULL;
		}
		master->list = NULL;
	}
}

void	ft_delete_next_node_data(t_data *list)
{
	t_data	*temp;
	t_data	*delete;

	temp = list->next->next;
	delete = list->next;
	ft_clean_data_node(delete);
	free(delete);
	list->next = temp;
}
