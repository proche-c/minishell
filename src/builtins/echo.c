/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2023/08/20 19:13:58 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_echo_with_n(t_down *down, int fd)
{
	t_down	*temp;

	temp = down->next;
	while ((temp && ft_strncmp(temp->arg, "-n", 3) == 0)
		|| (temp && ft_strncmp(temp->arg, "-nn", 3) == 0))
	{
		temp = temp->next;
	}
	while (temp != NULL)
	{
		write(fd, temp->arg, ft_strlen(temp->arg));
		temp = temp->next;
		if (temp != NULL)
			write(fd, " ", 1);
	}
}

static void	ft_echo_without_n(t_down *down, int fd)
{
	t_down	*temp;

	temp = down;
	while (temp != NULL)
	{
		write(fd, temp->arg, ft_strlen(temp->arg));
		temp = temp->next;
		if (temp != NULL)
			write(fd, " ", 1);
	}
	write(fd, "\n", 1);
}

void	ft_echo(t_data *data, int fd)
{
	t_down	*temp;

	if (data->down)
		temp = data->down;
	else
	{
		write(1, "\n", fd);
		return ;
	}
	if (data->num_args > 0)
	{
		if (ft_strncmp(temp->arg, "-n", 3) == 0
			|| ft_strncmp(temp->arg, "-nn", 3) == 0)
		{
			ft_echo_with_n(temp, fd);
		}
		else
			ft_echo_without_n(temp, fd);
	}
	else
		write(fd, "\n", 1);
	g_returnvalue = 0;
}
