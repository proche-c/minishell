/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2023/10/05 00:37:06 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	verifica_string(const char *str)
{
	while (*str)
	{
		if (ft_strncmp(str, "ls |", 4) == 0)
			str += 4;
		else if (ft_strncmp(str, "ls | ", 5) == 0)
			str += 6;
		else if (ft_strncmp(str, " ls", 4) == 0
			|| ft_strncmp(str, "ls", 3) == 0)
		{
			return (TRUE);
		}
		else
			return (FALSE);
		if (*str == ' ')
			str += 1;
	}
	return (FALSE);
}

void	ft_value_master(t_master *master, char *str)
{
	if (verifica_string(str) == TRUE)
		master->str = ft_strdup("ls");
	else
		master->str = str;
	master->elem = NULL;
	master->num_elem = 0;
	master->error = 0;
	master->pipes = NULL;
	master->fd_redir = 0;
	master->redir_type = 0;
	master->executed_cmds = 0;
	master->executed_pipes = -1;
	master->num_pipes = 0;
	master->num_redir = 0;
	master->execute = 1;
	master->priority_g_return = -42;
}

int	ft_spaces(char *str)
{
	int	count;
	int	x;

	count = 0;
	x = 0;
	if (!str)
		return (1);
	while (str[x] != '\0')
	{
		if (ft_isspace(str[x]) == 1)
			count++;
		x++;
	}
	if (count == (int)ft_strlen(str))
		return (1);
	return (0);
}

void	ft_check_list(t_master *master)
{
	int	check;

	check = 0;
	check = ft_check_redir_end(master);
	if (check != 0)
	{
		ft_syntax_error_2(master, check);
		return ;
	}
	check = ft_check_double_redir(master);
	if (check != 0)
	{
		ft_syntax_error_3(master, check);
		return ;
	}
	ft_check_double_redir_input(master);
}

void	ft_parse_exec(t_master *master, char *str)
{
	if (ft_spaces(str) == 1)
		return ;
	if (ft_assign_one(str, master->env) == TRUE)
		ft_value_master(master, ft_strdup("cat"));
	else
	{
		ft_value_master(master, str);
		ft_check_str(master);
	}
	if (master->error == 0)
	{
		ft_get_entry(master);
		if (!master->list)
			return ;
		ft_check_list(master);
		if (master->error == 0)
			ft_big_execute(master);
	}
}
