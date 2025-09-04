/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42barcelona.    +#+  +:+       +#+        */
/*   By: proche-c <proche-c@student.42barcelona.  +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2023/07/08 20:20:47 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_check_quote(t_master *master)
{
	char	*str_add;
	char	*aux;
	int		quote;
	int		dquote;

	quote = ft_find_quote(master->str, 1, ft_strlen(master->str) - 1);
	dquote = ft_find_quote(master->str, 2, ft_strlen(master->str) - 1);
	while (quote % 2 != 0 || dquote % 2 != 0)
	{
		aux = ft_strdup(master->str);
		str_add = readline(ANSI_COLOR_SHELL"🤖 dquote ➤ "ANSI_COLOR_RESET);
		free(master->str);
		master->str = ft_strjoin(aux, str_add);
		free(str_add);
		free(aux);
		quote = ft_find_quote(master->str, 1, ft_strlen(master->str) - 1);
		dquote = ft_find_quote(master->str, 2, ft_strlen(master->str) - 1);
	}
}

void	ft_check_end_pipe(t_master *master)
{
	int		len;
	char	*str_add;
	char	*aux;

	len = ft_strlen(master->str);
	while (master->str[len - 1] == '|' && master->str[len - 2] != '|')
	{
		aux = ft_strdup(master->str);
		str_add = readline(ANSI_COLOR_SHELL"🤖 Pipe ➤ "ANSI_COLOR_RESET);
		free(master->str);
		master->str = ft_strjoin(aux, str_add);
		free(str_add);
		free(aux);
		len = ft_strlen(master->str);
	}
}

void	ft_check_pipes(t_master *master)
{
	ft_check_start_pipe(master);
	if (master->error == 0)
		ft_check_double_pipe(master);
	if (master->error == 0)
		ft_check_re_pipes(master);
}

void	ft_check_str(t_master *master)
{
	ft_check_quote(master);
	ft_check_end_pipe(master);
	ft_check_pipes(master);
}
