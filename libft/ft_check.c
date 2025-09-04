/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lists.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2023/10/05 10:04:42 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_check_args_re(t_master *master)
{
	int		x;
	t_data	*temp;

	x = 0;
	if (!master->list)
		return ;
	temp = master->list;
	while (temp)
	{
		x++;
		temp = temp->next;
	}
	ft_assign_all(master, master->str, x);
}
