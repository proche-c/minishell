/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42barcelona.    +#+  +:+       +#+        */
/*   By: proche-c <proche-c@student.42barcelona.  +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2023/07/08 20:20:47 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_case(t_master *master, t_data *node, t_data *pipe, t_down *d)
{
	node->cmd = ft_strdup("echo");
	node->num_args = 1;
	node->down = d;
	pipe->type = PIPE;
	master->num_pipes++;
}

void	ft_give_values(t_master *master, t_data *node, t_data *p, t_data *t)
{
	int	x;

	x = 0;
	while (t)
	{
		if (t->type == 5)
			break ;
		x++;
		t = t->next;
	}
	t = master->list;
	while (t)
	{
		if (t->type == PIPE && x == 2)
		{
			node->next = p;
			p->next = t->next;
			t->next = node;
		}
		t = t->next;
		x--;
	}
}

void	ft_delete_node(t_data *temp)
{
	while (temp)
	{
		if (temp->next->type == 5)
		{
			ft_delete_next_node_data(temp);
			ft_delete_next_node_data(temp);
			break ;
		}
		temp = temp->next;
	}
}

void	ft_create_case_double_redir_input(t_master *master, char *str)
{
	t_data	*new_node;
	t_down	*new_down;
	t_data	*pipe;
	t_data	*temp;

	temp = master->list;
	new_node = ft_new_cmd(master);
	new_down = ft_down_new(master, str);
	free(str);
	pipe = ft_new_cmd(master);
	ft_init_case(master, new_node, pipe, new_down);
	if (master->list->next->type == 5)
	{
		new_node->next = pipe;
		pipe->next = master->list;
		master->list = new_node;
	}
	else
		ft_give_values(master, new_node, pipe, temp);
	temp = master->list;
	ft_delete_node(temp);
}

char	*ft_get_new_str(char *str, char *buf)
{
	char	*aux;

	aux = NULL;
	if (!str)
		str = ft_strdup(buf);
	else
	{
		aux = ft_strjoin(str, "\n");
		free(str);
		str = ft_strjoin(aux, buf);
		free(aux);
	}
	return (str);
}
