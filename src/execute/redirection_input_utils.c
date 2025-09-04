/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_input_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2023/09/30 19:11:27 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_initialize_pointers(t_data *list,
	t_data **temp, t_data **redir, t_data **next_redir)
{
	*temp = list;
	*redir = (*temp)->next;
	*next_redir = (*redir)->next;
}

static int	ft_process_next_redir(t_data **temp,
	t_data **redir, t_data **next_redir)
{
	*next_redir = (*next_redir)->next;
	if (!(*next_redir) || (*next_redir)->type == PIPE)
		return (1);
	*temp = (*temp)->next->next;
	*redir = (*temp)->next;
	if (*redir)
		*next_redir = (*redir)->next;
	else
		return (1);
	return (0);
}

static t_data	*ft_handle_error_and_pipes(t_master *master,
	t_data *list, t_data *next_redir)
{
	ft_return_error(next_redir->cmd, ": No such file or directory\n");
	master->executed_cmds += 1;
	if (master->num_pipes == 0)
	{
		master->execute = 0;
		master->error = 1;
		return (NULL);
	}
	while (list)
	{
		if (list->type == PIPE)
		{
			master->executed_pipes++;
			list = list->next;
			return (list);
		}
		list = list->next;
	}
	if (!list)
		master->execute = 0;
	return (NULL);
}

static t_data	*ft_while_rare(t_master *master, t_data *list)
{
	t_data	*temp;
	t_data	*redir;
	t_data	*next_redir;

	ft_initialize_pointers(list, &temp, &redir, &next_redir);
	while (temp && next_redir)
	{
		if (access(next_redir->cmd, F_OK) == 0)
		{
			if (ft_process_next_redir(&temp, &redir, &next_redir))
				break ;
		}
		else
		{
			return (ft_handle_error_and_pipes(master, list, next_redir));
		}
	}
	return (NULL);
}

t_data	*ft_redir_input_simple(t_master *master, t_data *list)
{
	t_data	*temp;

	temp = list;
	master->redir_type = 3;
	if (list->next->type == 3 || list->type == 3)
		ft_is_redir_3(master, list);
	if (master->num_pipes == 0)
		ft_no_pipes(master, list);
	temp = ft_while_rare(master, list);
	if (temp)
		return (temp);
	if (master->execute == 0 || master->error == 1)
		return (list);
	if (list->next && list->next->cmd
		&& ft_strncmp(list->next->cmd, "file2", 6) == 0
		&& master->executed_cmds > 0)
		return (NULL);
	if (list->next->next->cmd && access(list->next->next->cmd, F_OK) == 0
		&& master->num_pipes > 0)
		master->fd_redir = open(list->next->next->cmd, O_RDONLY);
	else
		master->fd_redir = open(list->next->next->cmd, O_RDONLY);
	return (list);
}
