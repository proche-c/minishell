/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2023/07/01 11:51:10 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_cd_error_res_is_not_null(char *dir, char *res)
{
	struct stat	p_file_stat;
	char		*p_dir;

	p_dir = ft_substr(dir, 0, ft_strlen(dir) - ft_strlen(res));
	if (access(p_dir, F_OK) != 0)
		ft_return_error_3("cd: ", dir, ": No such file or directory\n");
	else if (stat(p_dir, &p_file_stat) == 0)
	{
		if (S_ISDIR(p_file_stat.st_mode) == 0)
			ft_return_error_3("cd: ", dir, ": Not a directory\n");
		else if (access(p_dir, R_OK) != 0
			|| access(p_dir, W_OK) != 0
			|| access(p_dir, X_OK) != 0)
			ft_return_error_3("cd: ", dir, ": Permission denied\n");
	}
	free(p_dir);
}

void	ft_cd_error_is_null(char *dir)
{
	struct stat	file_stat;

	if (access(dir, F_OK) != 0)
		ft_return_error_3("cd: ", dir, ": No such file or directory\n");
	else if (stat(dir, &file_stat) == 0)
	{
		if (S_ISDIR(file_stat.st_mode) == 0)
			ft_return_error_3("cd: ", dir, ": Not a directory\n");
		else if (access(dir, R_OK) != 0
			|| access(dir, W_OK) != 0
			|| access(dir, X_OK) != 0)
			ft_return_error_3("cd: ", dir, ": Permission denied\n");
	}
}

void	ft_cd_error(char *dir)
{
	char	*res;

	if (ft_strlen(dir) >= 256)
		ft_return_error_3("cd: ", dir, ": File name too long\n");
	res = ft_strrchr(dir, '/');
	if (res != NULL)
		ft_cd_error_res_is_not_null(dir, res);
	else
		ft_cd_error_is_null(dir);
	g_returnvalue = 1;
}
