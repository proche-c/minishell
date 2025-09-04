/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42barcelona.    +#+  +:+       +#+        */
/*   By: proche-c <proche-c@student.42barcelona.  +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2023/08/20 23:22:13 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envp	*ft_new_envp(char *key, char *value)
{
	t_envp	*envp;

	envp = (t_envp *)malloc(sizeof(t_envp));
	if (envp == NULL)
		return (NULL);
	envp->key = ft_strdup(key);
	if (value)
		envp->value = ft_strdup(value);
	else
		envp->value = NULL;
	envp->next = NULL;
	return (envp);
}

t_envp	*ft_lst_last(t_envp *list)
{
	while (list != NULL)
	{
		if (list->next == NULL)
			return (list);
		list = list->next;
	}
	return (list);
}

int	ft_envpsize(t_envp *lst)
{
	t_envp	*temp;
	int		i;

	temp = lst;
	i = 0;
	while (temp)
	{
		temp = temp->next;
		i++;
	}
	return (i);
}
