/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2023/07/01 11:48:34 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_create_new_envp_char(char **envp)
{
	char	**newenvp;
	int		x;

	x = 0;
	newenvp = (char **)malloc(sizeof(char *) * (ft_len_envp(envp) + 1));
	if (!newenvp)
		return (NULL);
	while (envp[x] != NULL)
	{
		newenvp[x] = ft_strdup(envp[x]);
		x++;
	}
	newenvp[x] = NULL;
	ft_order_envp(newenvp);
	return (newenvp);
}
