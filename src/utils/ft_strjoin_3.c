/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42barcelona.    +#+  +:+       +#+        */
/*   By: proche-c <proche-c@student.42barcelona.  +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2023/08/20 23:07:01 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_get_length(char *s1, char *s2, char *s3)
{
	int	length;

	length = 0;
	if (s1 != NULL)
		length = ft_strlen(s1);
	if (s2 != NULL)
		length = length + ft_strlen(s2);
	if (s3 != NULL)
		length = length + ft_strlen(s3);
	return (length);
}

static char	*ft_get_strjoin(char *s1, char *s2, char *s3, char *result)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (s1)
		while (s1[i])
			result[j++] = s1[i++];
	i = 0;
	if (s2)
		while (s2[i])
			result[j++] = s2[i++];
	i = 0;
	if (s3)
		while (s3[i])
			result[j++] = s3[i++];
	result[j] = '\0';
	return (result);
}

char	*ft_strjoin_3(char *s1, char *s2, char *s3, t_master *master)
{
	char	*result;
	int		length;

	length = ft_get_length(s1, s2, s3);
	result = NULL;
	result = malloc(sizeof(const char) * (length + 1));
	if (!result)
		master->error = 1;
	else
	{
		result = ft_get_strjoin(s1, s2, s3, result);
	}
	return (result);
}
