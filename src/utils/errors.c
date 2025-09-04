/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42barcelona.    +#+  +:+       +#+        */
/*   By: proche-c <proche-c@student.42barcelona.  +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2023/08/20 23:06:57 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_syntax_error(t_master *master)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
	master->error = 1;
	g_returnvalue = 2;
}

void	ft_tilde_error(t_master *master, char *mse)
{
	ft_putstr_fd(master->home, 2);
	ft_putstr_fd(mse, 2);
	master->error = 1;
	g_returnvalue = 126;
}

void	ft_tilde_error_2(t_master *master, char *mse)
{
	ft_putstr_fd(master->home, 2);
	ft_putstr_fd(mse, 2);
	master->error = 1;
	g_returnvalue = 127;
}

void	ft_syntax_error_2(t_master *master, int check)
{
	if (check == 1)
		ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
	else if (check == 2)
		ft_putstr_fd("syntax error near unexpected token `<'\n", 2);
	master->error = 1;
	g_returnvalue = 2;
}

void	ft_syntax_error_3(t_master *master, int check)
{
	if (check == 2)
		ft_putstr_fd("syntax error near unexpected token `>'\n", 2);
	if (check == 3)
		ft_putstr_fd("syntax error near unexpected token `<'\n", 2);
	if (check == 4)
		ft_putstr_fd("syntax error near unexpected token `>>'\n", 2);
	if (check == 5)
		ft_putstr_fd("syntax error near unexpected token `<<'\n", 2);
	master->error = 1;
	g_returnvalue = 2;
}
