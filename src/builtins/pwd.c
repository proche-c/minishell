/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2023/07/02 17:59:18 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_master *master)
{
	if (master->pwdflag == 1)
		ft_pwd_1(master);
	else
		ft_pwd_0();
}

void	ft_pwd_0(void)
{
	char	*buf;
	char	*aux;

	aux = NULL;
	buf = (char *)malloc((MAXPATHLEN + 1) * sizeof(char));
	if (!buf)
		return ;
	getcwd(buf, MAXPATHLEN);
	aux = ft_strjoin(buf, "\n");
	ft_putstr_fd(aux, 1);
	free(buf);
	free(aux);
	g_returnvalue = 0;
}

void	ft_pwd_1(t_master *master)
{
	char	*pwd;
	char	*aux;

	aux = ft_get_value_envp(master, "PWD");
	if (aux[ft_strlen(aux) - 1] != '.')
	{
		master->pwdflag = 0;
		ft_pwd_0();
	}
	else
	{
		pwd = ft_strjoin(aux, "\n");
		ft_putstr_fd(pwd, 1);
		free(pwd);
		g_returnvalue = 0;
	}
	free(aux);
}

char	*ft_my_path(void)
{
	char	*buf;

	buf = (char *)malloc((MAXPATHLEN + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	getcwd(buf, MAXPATHLEN);
	return (buf);
}
