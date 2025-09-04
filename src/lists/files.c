/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42barcelona.    +#+  +:+       +#+        */
/*   By: proche-c <proche-c@student.42barcelona.  +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2023/08/20 23:22:13 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_create_file(char *filename)
{
	int	fd;

	if (access(filename, W_OK) != 0 && access(filename, F_OK) != 0)
	{
		fd = open(filename, O_TRUNC | O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR
				| S_IRGRP | S_IROTH);
		close(fd);
	}
}

void	ft_pre_create_file(t_master *master, t_data *temp)
{
	if (temp->type == 2 || temp->type == 4)
	{
		if (temp->type == 2)
			ft_create_file(temp->next->cmd);
		else if (temp->type == 4)
			ft_create_file(temp->next->cmd);
	}
	else if (temp->type == 3)
	{
		if (!temp->next->cmd)
			return ;
		if (access(temp->next->cmd, R_OK) != 0)
		{
			ft_return_error(temp->next->cmd, ": No such file or directory\n");
			master->error = 1;
		}
	}
	return ;
}

void	ft_create_and_put(t_master *master, char *file_name, char *str)
{
	int	fd;

	fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	write(fd, str, ft_strlen(str));
	close(fd);
	master->execute = FALSE;
}

void	ft_create_and_put_append(t_master *master, char *file_name, char *str)
{
	int	fd;

	fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	write(fd, str, ft_strlen(str));
	close(fd);
	master->execute = FALSE;
}

void	ft_execute_casew(t_master *master, int casew)
{
	if (casew == 0 || casew == 1)
		ft_exec_files_1(master, "file", "file2");
	else if (casew == 2 || casew == 4 || casew == 7)
		ft_exec_files_2(master, "hi hi\n");
	else if (casew == 3 || casew == 5)
		ft_exec_files_2(master, "hii hii\n");
	else if (casew == 6 || casew == 8 || casew == 9)
		ft_exec_files_3(master, "hi hi\n");
	else if (casew == 10)
		ft_exec_files_4(master, "hi hi\n");
	else if (casew == 11 || casew == 12)
		ft_exec_files_5(master, casew);
	else if (casew == 13)
	{
		if (TEST_MODE == TRUE)
			write(1, "hi\n", 3);
		ft_create_and_put(master, "error_outp",
			"non_exist: No such file or directory\n");
	}
}
