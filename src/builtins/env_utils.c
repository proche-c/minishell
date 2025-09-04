/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2023/09/30 12:51:43 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_key(char *str)
{
	char	*key;
	int		len;
	int		y;

	len = 0;
	y = 0;
	while (str[len] != '\0' && str[len] != '=')
		len++;
	key = (char *)malloc(sizeof(char) * (len + 1));
	if (!key)
		return (NULL);
	while (y < len)
	{
		key[y] = str[y];
		y++;
	}
	key[y] = '\0';
	return (key);
}

char	*ft_get_value(char *str)
{
	char	*value;
	int		x;
	int		y;
	int		len;
	int		newlen;

	x = 0;
	y = 0;
	len = ft_strlen(str);
	while (str[x] != '\0' && str[x] != '=')
		x++;
	if (str[x + 1] == '\0')
		return (NULL);
	newlen = (len - x) - 1;
	value = (char *)malloc(sizeof(char) * (len - x));
	if (!value || newlen <= 0)
		return (NULL);
	while (y < newlen)
	{
		value[y] = str[x + 1];
		x++;
		y++;
	}
	value[y] = '\0';
	return (value);
}

int	ft_len_envp(char **envp)
{
	int	x;

	x = 0;
	while (envp[x] != NULL)
		x++;
	return (x);
}

void	ft_order_envp(char **envp)
{
	char	*temp;
	int		x;
	int		y;
	int		size;

	x = 0;
	y = 0;
	size = ft_len_envp(envp);
	while (x < size)
	{
		y = 0;
		while (y < (size - 1))
		{
			if (ft_strncmp(envp[y], envp[y + 1], ft_strlen(envp[y])) > 0)
			{
				temp = envp[y];
				envp[y] = envp[y + 1];
				envp[y + 1] = temp;
			}
			y++;
		}
		x++;
	}
	size = ft_len_envp(envp);
}

int	ft_search_equal(char *str)
{
	int	x;

	x = 0;
	while (str[x] != '\0')
	{
		if (str[x] == '=')
			return (1);
		x++;
	}
	return (0);
}
