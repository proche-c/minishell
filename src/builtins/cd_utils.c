/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2023/09/30 19:12:57 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_aux_is_cd(t_master *master, char *aux)
{
	char	*oldpwd;
	char	*my_path;

	my_path = ft_my_path();
	printf("%s\n", aux);
	oldpwd = ft_strjoin("OLDPWD=", my_path);
	chdir(aux);
	ft_cd_export(master, oldpwd);
	free(oldpwd);
	free(my_path);
	aux = NULL;
}

static void	ft_aux_is_cd_2(t_master *master, char *aux)
{
	struct stat	file_stat;

	if (stat(aux, &file_stat) == 0 && S_ISDIR(file_stat.st_mode) != 0
		&& access(aux, F_OK | R_OK | W_OK | X_OK) == 0)
	{
		ft_aux_is_cd(master, aux);
		aux = NULL;
	}
	else
	{
		ft_cd_error_is_null(aux);
		g_returnvalue = 1;
	}
	if (aux)
		free(aux);
}

void	ft_is_cd(t_master *master, t_data *list)
{
	char	*aux;

	master->pwdflag = 0;
	if (list->num_args == 0 || ft_strncmp(list->down->arg, "~", 2) == 0)
		ft_cd(master, master->home);
	else if (list->down->arg[0] == '-')
	{
		aux = ft_get_value_export(master, "OLDPWD");
		if (!aux)
		{
			printf("cd: OLDPWD not set\n");
			return ;
		}
		ft_aux_is_cd_2(master, aux);
	}
	else if (list->num_args > 0)
		ft_cd(master, list->down->arg);
}
