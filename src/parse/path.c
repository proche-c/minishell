/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veaz <veaz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2023/06/01 13:36:31 by veaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envp	*ft_find_path(t_master *master)
{
	t_envp	*temp;
	char	*p;
	int		res;

	p = "PATH";
	temp = master->envp;
	while (temp->key)
	{
		res = ft_strncmp(p, temp->key, 5);
		if (res == 0)
		{
			return (temp);
		}
		temp = temp->next;
	}
	return (temp);
}
