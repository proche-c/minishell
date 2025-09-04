/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2023/09/30 12:51:35 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd_export(t_master *master, char *oldpwd)
{
	char	*pwd;
	char	*aux;

	aux = ft_my_path();
	pwd = ft_strjoin("PWD=", aux);
	ft_unset(master, master->envp, "PWD");
	ft_unset(master, master->envp, "OLDPWD");
	ft_export_with_var(master, oldpwd);
	ft_export_with_var(master, pwd);
	free(pwd);
	free(aux);
	g_returnvalue = 0;
}

static	void	ft_error_access(t_master *master, char *mypath, char *oldpwd)
{
	char	*pwd;

	master->pwdflag = 1;
	pwd = ft_strjoin_3("PWD=", mypath, "/.", master);
	ft_export_with_var(master, oldpwd);
	ft_export_with_var(master, pwd);
	ft_return_error_3("cd: ", "error retrieving current directory: getcwd",
		": cannot access parent directories: No such file or directory\n");
	free(pwd);
	g_returnvalue = 0;
}

void	ft_cd(t_master *master, char *dir)
{
	char	*oldpwd;
	char	*mypath;

	mypath = ft_my_path();
	oldpwd = ft_strjoin("OLDPWD=", mypath);
	if (access(mypath, F_OK) != 0 && ft_strncmp(dir, ".", 2) == 0)
		ft_error_access(master, mypath, oldpwd);
	else
	{
		if (dir[0] != '\0')
		{
			if (chdir(dir) < 0)
				ft_cd_error(dir);
			else
				ft_cd_export(master, oldpwd);
		}
		else
			g_returnvalue = 0;
	}
	if (oldpwd)
		free(oldpwd);
	if (mypath)
		free(mypath);
}
