/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42barcelona.    +#+  +:+       +#+        */
/*   By: proche-c <proche-c@student.42barcelona.  +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2023/07/08 20:20:47 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_check_start_pipe(t_master *master)
{
	int	start;

	start = 0;
	while (master->str[start] == ' ')
		start++;
	if (master->str[start] == '|')
		ft_syntax_error(master);
}

void	ft_check_double_pipe(t_master *master)
{
	int	i;

	i = 0;
	if (master->error == 0 && ft_strlen(master->str) > 1)
	{
		while (master->str[i] != '\0' && master->str[i] != '|')
		{
			i++;
			if (master->str[i] == '|' && ft_is_quoted(master->str, i) == 0)
			{
				i++;
				while (ft_isspace(master->str[i]) == 1)
					i++;
				if (master->str[i] == '|')
				{
					ft_syntax_error(master);
					break ;
				}
			}
		}
	}
}

void	ft_check_double_re_pipe(t_master *master, char c)
{
	int	start;

	start = 0;
	while (ft_isspace(master->str[start]) == 1)
		start++;
	if (master->str[start] == c && ft_is_quoted(master->str, start) == 0)
	{
		start++;
		while (ft_isspace(master->str[start]) == 1)
			start++;
		if (master->str[start] == c)
		{
			start++;
			while (ft_isspace(master->str[start]) == 1)
				start++;
			if (master->str[start] == '|')
				ft_syntax_error(master);
		}
	}
}

void	ft_check_single_re_pipe(t_master *master, char c)
{
	int	start;

	start = 0;
	while (ft_isspace(master->str[start]) == 1)
		start++;
	if (master->str[start] == c && ft_is_quoted(master->str, start) == 0)
	{
		start++;
		while (ft_isspace(master->str[start]) == 1)
			start++;
		if (master->str[start] == '|')
			ft_syntax_error(master);
	}
}
