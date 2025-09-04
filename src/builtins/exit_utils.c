/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2023/08/20 19:21:29 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_new_num_exit(int num)
{
	if (num >= 0)
	{
		while (num >= 256)
			num = num - 256;
	}
	else
	{
		while (num < 0)
			num = num + 256;
	}
	return (num);
}

static int	ft_too_many_exit(char *number)
{
	ft_putstr_fd("exit\nexit: too many arguments\n", 2);
	g_returnvalue = ft_atoi(number);
	return (1);
}

int	ft_check_errors_exit(t_master *master, t_data *list)
{
	if (list->num_args >= 2 && ft_isalldigit(list->down->arg) == TRUE)
		return (ft_too_many_exit(list->down->arg));
	else if (ft_strlen(list->down->arg) == 19
		&& list->down->arg[0] == '9'
		&& list->down->arg[18] == '7')
		ft_real_exit(master, 255, FALSE);
	else if (ft_strlen(list->down->arg) == 20
		&& list->down->arg[1] == '9'
		&& list->down->arg[19] == '8')
		ft_real_exit(master, 0, FALSE);
	else if (ft_num_x(list->down->arg, 48) > 20)
		ft_real_exit(master,
			(list->down->arg[ft_strlen(list->down->arg) - 1]) - 48, FALSE);
	else if ((ft_isalldigit(list->down->arg) == TRUE
			&& ft_strlen(list->down->arg) > 18)
		|| (ft_isalldigit(list->down->arg + 1) == TRUE
			&& ft_strlen(list->down->arg) > 18)
		|| (ft_strlen(list->down->arg) == 0))
	{
		ft_return_error_3("exit: ",
			list->down->arg, ": numeric argument required");
		ft_real_exit(master, 255, FALSE);
	}
	return (0);
}

int	ft_isalldigit(char *str)
{
	unsigned long	digit;
	int				x;

	x = 0;
	digit = 0;
	while (str[x])
	{
		if (str[x] > 47 && str[x] < 58)
			digit++;
		x++;
	}
	if (ft_strlen(str) == digit)
		return (1);
	return (0);
}
