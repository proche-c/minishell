/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_separate_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42barcelona.    +#+  +:+       +#+        */
/*   By: proche-c <proche-c@student.42barcelona.  +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2023/07/05 21:32:30 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_init_cmd(t_master *master)
{
	char	**cmd;

	cmd = malloc(sizeof(char *) * 2);
	if (!cmd)
		master->error = 1;
	cmd[0] = NULL;
	cmd[1] = NULL;
	return (cmd);
}

int	ft_get_new_i(char **strin, int i)
{
	int	k;

	k = i;
	while (ft_isspace(strin[1][k]) == 1 && strin[1][k] != '\0')
		k++;
	while (ft_stop(strin[1], k, strin[0]) == 0 && strin[1][k] != '\0')
		k++;
	return (k);
}

int	ft_get_len_cmd(char **strin, int i, int new_i)
{
	int	quotes;
	int	dquotes;

	while (ft_isspace(strin[1][i]) == 1 && strin[1][i] != '\0')
		i++;
	quotes = ft_count_quotes(strin[1], i, new_i, strin[0]);
	dquotes = ft_count_dquotes(strin[1], i, new_i, strin[0]);
	return (new_i - i - quotes - dquotes);
}

int	ft_stop(char *str, int k, char *q)
{
	int	quotes;
	int	dquotes;

	quotes = ft_count_quotes(str, 0, k, q);
	dquotes = ft_count_dquotes(str, 0, k, q);
	if (ft_isspace(str[k]) == 1 && quotes % 2 == 0 && dquotes % 2 == 0)
		return (1);
	return (0);
}
