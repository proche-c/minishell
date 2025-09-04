/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2023/10/01 20:05:22 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_strin(char **strin)
{
	if (strin[0] != NULL)
		free(strin[0]);
	if (strin[1] != NULL)
		free(strin[1]);
	free(strin);
}

void	ft_free_quo(t_data *data)
{
	t_quo	*aux;
	t_quo	*temp;

	aux = data->quo;
	while (aux != NULL)
	{
		temp = aux;
		aux = aux->next;
		free(temp);
	}
}

void	ft_clean_args(t_data *list_node)
{
	int		i;

	i = 0;
	while (list_node->args[i])
	{
		free(list_node->args[i]);
		list_node->args[i] = NULL;
		i++;
	}
	free(list_node->args);
	list_node->args = NULL;
}
