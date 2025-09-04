/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2023/09/25 22:24:37 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_exit_not_normal(t_master *master, char *str)
{
	int	num;

	if (ft_isalldigit(str + 1) == TRUE)
	{
		num = ft_new_num_exit(ft_atoi(str));
		ft_real_exit(master, num, 4);
	}
	else
		ft_real_exit(master, 42, 4);
}

void	ft_exit_normal(t_master *master, char *str, int args)
{
	int	num;

	if (ft_isalldigit(str) == TRUE)
	{
		num = ft_new_num_exit(ft_atoi(str));
		if (args > 1)
		{
			ft_putstr_fd("exit: too many arguments2", 2);
			ft_real_exit(master, num, FALSE);
		}
		else
			ft_real_exit(master, num, TRUE);
	}
	else if ((str[0] == ' ' && ft_atoi(str) != 0)
		|| (str[ft_strlen(str) - 1] == ' ' && ft_atoi(str) != 0))
		ft_real_exit(master, ft_atoi(str), FALSE);
	else
	{
		ft_return_error_3("exit: ", str, ": numeric argument required");
		ft_real_exit(master, 255, FALSE);
	}
}

void	ft_exit_with_symbol(t_master *master, char *str)
{
	if (ft_strlen(str) == 1 || ft_isalldigit(str + 1) == FALSE)
	{
		ft_return_error_3("exit: ", str, ": numeric argument required");
		ft_real_exit(master, 255, FALSE);
	}
	else if (ft_isalldigit(str + 1) == TRUE)
		ft_exit_not_normal(master, str);
	ft_real_exit(master, 42, 4);
}

void	ft_exit(t_master *master, t_data *list)
{
	if (list->num_args < 1
		|| (list->num_args == 1 && ft_strncmp(list->down->arg, "--", 3) == 0))
		ft_real_exit(master, g_returnvalue, TRUE);
	if (ft_check_errors_exit(master, list) != 1)
	{
		if (ft_strncmp(list->down->arg, "+", 1) == 0
			|| ft_strncmp(list->down->arg, "-", 1) == 0)
			ft_exit_with_symbol(master, list->down->arg);
		else
		{
			if (ft_strlen(list->down->arg) < 11)
				ft_exit_normal(master, list->down->arg, list->num_args);
			if (ft_strlen(list->down->arg) > 21
				&& ft_isalldigit(list->down->arg) == TRUE
				&& ft_num_x(list->down->arg, '0') > 20)
				exit(list->down->arg[21] - 48);
			else
			{
				ft_return_error_3("exit: ",
					list->down->arg, ": numeric argument required");
				ft_real_exit(master, 255, FALSE);
			}
		}
	}
}

void	ft_real_exit(t_master *master, int num, int print)
{
	ft_clean_master_all(master);
	if (print == 24)
		ft_putstr_fd("exit\n", 2);
	exit(num);
}
