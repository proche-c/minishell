/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2023/08/20 22:10:42 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_create_pipes(t_master *master)
{
	int	x;

	x = 0;
	if (master->num_pipes > 0)
		master->pipes = malloc(master->num_pipes * sizeof(int *));
	else
		return ;
	if (!master->pipes)
		return ;
	while (x < master->num_pipes)
	{
		master->pipes[x] = malloc(2 * sizeof(int));
		if (!master->pipes[x])
			return ;
		pipe(master->pipes[x]);
		x++;
	}
}
