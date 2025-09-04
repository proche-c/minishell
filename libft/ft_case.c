/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_case.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2023/09/30 12:41:02 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_exec_files_1(t_master *master, char *file1, char *file2)
{
	int	fd;

	ft_create_and_put_append(master, file1, "hi hi\n");
	fd = open(file2, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR
			| S_IRGRP | S_IROTH);
	close(fd);
}

void	ft_exec_files_2(t_master *master, char *aux)
{
	int	fd;

	ft_create_and_put_append(master, "file", aux);
	fd = open("file2", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR
			| S_IRGRP | S_IROTH);
	close(fd);
	fd = open("file3", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR
			| S_IRGRP | S_IROTH);
	close(fd);
}

void	ft_exec_files_3(t_master *master, char *aux)
{
	int	fd;

	ft_create_and_put(master, "file", aux);
	fd = open("file2", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR
			| S_IRGRP | S_IROTH);
	close(fd);
	fd = open("file3", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR
			| S_IRGRP | S_IROTH);
	close(fd);
}

void	ft_exec_files_4(t_master *master, char *aux)
{
	int	fd;

	ft_create_and_put_append(master, "filec", aux);
	fd = open("filea", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR
			| S_IRGRP | S_IROTH);
	close(fd);
	fd = open("fileb", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR
			| S_IRGRP | S_IROTH);
	close(fd);
}

void	ft_exec_files_5(t_master *master, int casew)
{
	int	fd;

	if (casew == 11)
	{
		fd = open("wrong", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR
				| S_IRGRP | S_IROTH);
		close(fd);
		master->execute = 0;
	}
	else if (casew == 12)
	{
		printf("hi, I am the file2\n");
		master->execute = 0;
	}
}
