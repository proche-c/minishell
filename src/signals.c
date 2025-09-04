/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2023/08/20 23:09:04 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cc(int num)
{
	(void)num;
	printf("\n");
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
	g_returnvalue = 1;
}

void	ft_cc_execute(int num)
{
	(void)num;
	printf("^C\n");
	rl_replace_line("", 1);
	g_returnvalue = 130;
}

void	ft_cr(int num)
{
	(void)num;
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	ft_cr_execute(int num)
{
	(void)num;
	printf("^\\Quit: 3\n");
	rl_replace_line("", 1);
	g_returnvalue = 131;
}

void	ft_signals(void)
{
	struct termios	termios;

	if (tcgetattr(STDIN_FILENO, &termios) == -1)
		return ;
	termios.c_lflag &= ~(ECHOCTL);
	if (tcsetattr(STDIN_FILENO, TCSANOW, &termios) == -1)
		return ;
	signal(SIGINT, &ft_cc);
	signal (SIGQUIT, &ft_cr);
}
