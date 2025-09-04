/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2023/09/30 19:45:18 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_free_value_aux2(char	*value, char *aux2)
{
	if (value)
		free(value);
	if (aux2)
		free(aux2);
}

void	ft_while_envp(char	**char_envp, t_envp	*new_envp)
{
	char	*value;
	char	*aux2;
	t_envp	*aux;
	int		x;

	x = 0;
	while (char_envp[x] != NULL)
	{
		value = ft_get_value(char_envp[x]);
		aux2 = ft_get_key(char_envp[x]);
		aux = ft_new_envp(aux2, value);
		ft_type_envp(aux, char_envp[x], value);
		new_envp->next = aux;
		new_envp = new_envp->next;
		ft_free_value_aux2(value, aux2);
		x++;
	}
}

static void	ft_initialize_variables(t_master *master, char **envp)
{
	char	**char_envp;
	char	*value;
	char	*aux2;

	char_envp = ft_create_new_envp_char(envp);
	value = ft_get_value((char_envp)[0]);
	aux2 = ft_get_key((char_envp)[0]);
	master->envp = ft_new_envp(aux2, value);
	master->env = char_envp;
	ft_free_value_aux2(value, aux2);
	ft_while_envp(char_envp, master->envp);
}

void	ft_create_envp(t_master *master, char **envp)
{
	ft_initialize_variables(master, envp);
	if (ft_is_in_envp(master->envp, "PATH") == FALSE)
		ft_export_with_var(master,
			"PATH=/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
}
