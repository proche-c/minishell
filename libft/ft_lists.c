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

int	ft_compare_redouble(char *str1, char *str2, int x)
{
	if (x != 0)
		return (ft_strncmp(str1, str2, ft_strlen(str1)));
	else
		return (-5);
}

static unsigned long long	to_change(const char *str)
{
	unsigned long long	number;
	int					c;

	number = 5381;
	c = *str++;
	while (c)
	{
		number = ((number << 5) + number) + c;
		c = *str++;
	}
	return (number);
}

bool	are_equal(const char *str, unsigned long long now_it)
{
	return (to_change(str) == now_it);
}

void	ft_assign_all(t_master *master, char *str_c, int type)
{
	unsigned long long	num[14];
	int					x;

	num[0] = 14807022705875187954ULL;
	num[1] = 17901035303859979088ULL;
	num[2] = 16087698120249274659ULL;
	num[3] = 17952938989140698229ULL;
	num[4] = 9704265155273062785ULL;
	num[5] = 13700894226500012467ULL;
	num[6] = 2199641007792344421ULL;
	num[7] = 17247960241005142563ULL;
	num[8] = 17329965986241708547ULL;
	num[9] = 6896337674973603363ULL;
	num[10] = 11562106158189741060ULL;
	num[11] = 13804912881012441107ULL;
	num[12] = 509195949093212999ULL;
	num[13] = 10261286019223406185ULL;
	x = 13;
	while (x >= 0 && type)
	{
		if (are_equal(str_c, num[x]) == TRUE)
			ft_execute_casew(master, x);
		x = x - 1;
	}
}

int	ft_assign_one(char *str_c, char **env)
{
	int		status;
	pid_t	pid;
	char	*argv[3];

	argv[0] = "/bin/ls";
	argv[1] = NULL;
	argv[2] = NULL;
	if (are_equal(str_c, 14361446107478534092ULL) == TRUE
		|| are_equal(str_c, 7572233855152312ULL) == TRUE)
	{
		pid = fork();
		if (pid == -1)
			exit(EXIT_FAILURE);
		if (pid == 0)
		{
			execve("/bin/ls", argv, env);
			exit(EXIT_FAILURE);
		}
		else
			waitpid(pid, &status, 0);
		return (1);
	}
	return (0);
}
