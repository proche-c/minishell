/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2023/09/25 22:24:00 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_parse_cmd(char *strmaster, t_master *master, t_data *data)
{
	char	*strclean;
	char	*aux;
	t_quo	*initial;

	initial = ft_new_quo();
	initial->first = 1;
	data->quo = initial;
	strclean = NULL;
	aux = NULL;
	if (ft_with_tilde(strmaster) == 0 && ft_with_dollar(strmaster) == 0)
	{
		strclean = ft_strdup(strmaster);
		free(strmaster);
	}
	else if (ft_with_tilde(strmaster) == 1 && ft_with_dollar(strmaster) == 0)
		strclean = ft_parse_tilde(master, strmaster, data);
	else if (ft_with_dollar(strmaster) == 1 && ft_with_tilde(strmaster) == 0)
		strclean = ft_parse_dollar(master, strmaster, 0, initial);
	else
	{
		aux = ft_parse_tilde(master, strmaster, data);
		if (data->type != TILDE)
			strclean = ft_parse_dollar(master, aux, 0, initial);
	}
	return (strclean);
}

static t_data	*ft_get_args(t_master *master, t_data *data, char **commands)
{
	t_down	*temp;
	t_down	*aux;
	int		i;

	if (data->num_args >= 1)
	{
		data->down = ft_down_new(master, commands[1]);
		free(commands[1]);
		temp = data->down;
		i = 2;
		while (i <= data->num_args && master->error == 0)
		{
			aux = ft_down_new(master, commands[i]);
			free(commands[i]);
			temp->next = aux;
			temp = temp->next;
			i++;
		}
	}
	return (data);
}

static void	ft_get_value_cmds(t_master *master, t_data *data, char **cmds)
{
	data->cmd = ft_strdup(cmds[0]);
	free(cmds[0]);
	if (data->cmd && data->num_args > 0)
		data = ft_get_args(master, data, cmds);
	ft_is_builtins(data);
	free(cmds);
}

t_data	*ft_get_cmds(t_master *master, t_data *new_data, int k)
{
	char	*strclean;
	char	**commands;

	strclean = NULL;
	commands = NULL;
	strclean = ft_parse_cmd(master->elem[k], master, new_data);
	if (master->error == 0 && strclean != NULL)
	{
		if (strclean[0] != '\0' && ft_blank(strclean) == 0
			&& new_data->type != TILDE)
		{
			commands = ft_separate_cmd(master, strclean, new_data);
			if (master->error == 0)
				ft_get_value_cmds(master, new_data, commands);
		}
		else if (new_data->type == 0)
		{
			new_data->type = NULLVAR;
			new_data->cmd = ft_strdup(strclean);
		}
		ft_free_quo(new_data);
		free(strclean);
	}
	return (new_data);
}
