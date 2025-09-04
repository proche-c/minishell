/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_tilde.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veaz <veaz@student.42.fr>                  +#+  +:+       +#+        */
/*   By: proche-c <proche-c@student.42barcelona.  +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2023/06/03 21:58:24 by veaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_parse_tilde(t_master *master, char *strmaster, t_data *data)
{
	char	*aux;
	int		i;

	aux = NULL;
	i = 0;
	if (ft_is_tilde(strmaster, 0) == 1)
	{
		data->type = TILDE;
		ft_exec_tilde(master, strmaster, data);
		free(strmaster);
		return (NULL);
	}
	while (strmaster[i] != '\0' && master->error == 0 && strmaster != NULL)
	{
		if (ft_is_tilde(strmaster, i) == 1)
		{
			aux = ft_strdup(strmaster);
			free(strmaster);
			strmaster = ft_replace_tilde(master, aux, i);
			i = i + ft_strlen(master->home);
		}
		else
			i++;
	}
	return (strmaster);
}

void	ft_exec_tilde(t_master *master, char *strmaster, t_data *data)
{
	int		i;
	int		len;
	char	*dir;
	char	*value;

	i = 0;
	dir = NULL;
	value = NULL;
	while (strmaster[i] != '~')
		i++;
	len = 0;
	while (ft_isspace(strmaster[i + len]) == 0 && strmaster[i + len] != '\0')
		len++;
	value = ft_substr(strmaster, i + 1, len);
	dir = ft_strjoin(master->home, value);
	ft_eval_tilde(master, dir);
	free(data->quo);
	free(dir);
	free(value);
}

void	ft_eval_tilde(t_master *master, char *dir)
{
	struct stat	st;

	if (ft_strlen(dir) > 255)
		ft_tilde_error(master, ": File name too long\n");
	else if (stat(dir, &st) == 0 && (S_ISREG(st.st_mode)))
	{
		if (access(dir, R_OK) != 0 || access(dir, W_OK) != 0
			|| access(dir, X_OK) != 0)
			ft_tilde_error(master, ": Permission denied\n");
		else
			g_returnvalue = 0;
	}
	else if (stat(dir, &st) == 0 && (S_ISDIR(st.st_mode)))
		ft_tilde_error(master, ": is a directory\n");
	else
		ft_tilde_error_2(master, ": No such file or directory\n");
}

char	*ft_replace_tilde(t_master *master, char *aux, int i)
{
	char	*result;
	char	*rest;
	char	*start;
	int		len;

	result = NULL;
	rest = NULL;
	start = NULL;
	start = ft_substr(aux, 0, i);
	len = ft_strlen(aux) - i - ft_len_var(aux, i) - 1;
	rest = ft_substr(aux, i + ft_len_var(aux, i) + 1, len);
	result = ft_strjoin_3(start, master->home, rest, master);
	free(start);
	free(rest);
	free(aux);
	return (result);
}
