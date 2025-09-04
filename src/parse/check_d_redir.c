/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_d_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42barcelona.    +#+  +:+       +#+        */
/*   By: proche-c <proche-c@student.42barcelona.  +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2023/07/08 20:20:47 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_get_redirs(t_master *master)
{
	int		redirs;
	t_data	*temp;

	temp = master->list;
	redirs = 0;
	while (temp)
	{
		if (temp->type == PIPE)
			break ;
		else if (temp->type == 5)
			redirs++;
		temp = temp->next;
	}
	return (redirs);
}

char	*ft_get_end(t_master *master)
{
	char	*end;
	t_data	*temp;

	temp = master->list;
	end = NULL;
	while (temp)
	{
		if (temp->type == PIPE)
			break ;
		else if (temp->type == 5)
			end = temp->next->cmd;
		temp = temp->next;
	}
	return (end);
}

char	*ft_get_start(t_master *master, char *end)
{
	t_data	*temp;
	char	*start;

	temp = master->list;
	start = NULL;
	while (temp)
	{
		if (temp->type == PIPE)
		{
			break ;
		}
		else if (temp->type == 5)
		{
			if (end == NULL)
				end = temp->next->cmd;
			else
			{
				start = end;
				end = temp->next->cmd;
			}
		}
		temp = temp->next;
	}
	return (start);
}

void	ft_process_redir(t_master *master, char *end, char *start, int redirs)
{
	char	*str;
	char	*buf;

	str = NULL;
	buf = NULL;
	while (1)
	{
		buf = readline(ANSI_COLOR_SHELL"➤ "ANSI_COLOR_RESET);
		if (redirs > 1)
		{
			if (ft_strncmp(buf, start, ft_strlen(start)) == 0)
				redirs = 1;
		}
		else if (ft_strncmp(buf, end, ft_strlen(end)) == 0 && redirs == 1)
		{
			free(buf);
			ft_create_case_double_redir_input(master, str);
			master->num_redir--;
			return ;
		}
		else
			str = ft_get_new_str(str, buf);
		free(buf);
	}
}

void	ft_check_double_redir_input(t_master *master)
{
	t_data	*temp;
	char	*start;
	char	*end;
	int		redirs;

	start = NULL;
	end = NULL;
	redirs = ft_get_redirs(master);
	end = ft_get_end(master);
	if (redirs > 1)
		start = ft_get_start(master, end);
	temp = master->list;
	while (temp)
	{
		if (temp->type == 5)
		{
			ft_process_redir(master, end, start, redirs);
		}
		temp = temp->next;
	}
}
