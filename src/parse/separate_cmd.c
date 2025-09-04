/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separate_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42barcelona.    +#+  +:+       +#+        */
/*   By: proche-c <proche-c@student.42barcelona.  +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2023/07/05 21:32:30 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_separate_cmd(t_master *master, char *strclean, t_data *data)
{
	char	**result;
	char	**strin;
	int		num_cmds;

	result = NULL;
	strin = NULL;
	strin = ft_init_cmd(master);
	strin[0] = ft_get_real_quotes(data->quo, master, ft_strlen(strclean));
	if (master->error == 0)
	{
		num_cmds = ft_get_num_cmds(strclean, strin[0]);
		data->num_args = num_cmds - 1;
		strin[1] = ft_strdup(strclean);
		result = ft_assign_cmds(master, strin, num_cmds);
	}
	ft_free_strin(strin);
	return (result);
}

int	ft_get_num_cmds(char *strclean, char *realq)
{
	int	result;
	int	i;

	i = 0;
	result = 0;
	if (ft_stop(strclean, i, realq) == 0)
	{
		result++;
		i++;
	}
	while (strclean[i] != '\0')
	{
		if (ft_stop(strclean, i, realq) == 0
			&& ft_stop(strclean, i - 1, realq) == 1)
			result++;
		i++;
	}
	return (result);
}

char	**ft_assign_cmds(t_master *master, char **strin, int num_cmds)
{
	int		i;
	int		new_i;
	int		j;
	int		len;
	char	**result;

	i = 0;
	j = 0;
	result = malloc(sizeof(char *) * (num_cmds + 1));
	if (!result)
		master->error = 1;
	while (strin[1][i] != '\0' && j < num_cmds && master->error == 0)
	{
		new_i = ft_get_new_i(strin, i);
		len = ft_get_len_cmd(strin, i, new_i);
		result[j] = malloc(sizeof(char) * (len + 1));
		if (result[j])
			result[j] = ft_get_parsed_cmd(strin, i, len, result[j]);
		j++;
		i = new_i;
		while (ft_isspace(strin[1][i]) == 1)
			i++;
	}
	result[j] = 0;
	return (result);
}

char	*ft_get_parsed_cmd(char **strin, int i, int len, char *result)
{
	int	k;
	int	quotes;
	int	dquotes;

	quotes = 0;
	dquotes = 0;
	while (ft_isspace(strin[1][i]) == 1 && strin[1][i] != '\0')
		i++;
	k = 0;
	while (k < len)
	{
		if (strin[1][i] == '\'' && dquotes % 2 == 0 && strin[0][i] == '0')
			quotes++;
		else if (strin[1][i] == '"' && quotes % 2 == 0 && strin[0][i] == '0')
			dquotes++;
		else
		{
			result[k] = strin[1][i];
			k++;
		}
		i++;
	}
	result[k] = '\0';
	return (result);
}
