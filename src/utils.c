/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncrivell <ncrivell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:17:38 by ncrivell          #+#    #+#             */
/*   Updated: 2025/03/17 19:48:14 by ncrivell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>
#include "pipex.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	i = 0;
	while ((s1[i] == s2[i]) && s1[i] && s2[i] && (i < n))
		i++;
	if (i == n)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	ft_init_struct(t_pip *pip)
{
	pip->infile = -1;
	pip->outfile = -1;
	pip->pipe_fd[0] = -1;
	pip->pipe_fd[1] = -1;
	pip->path_one = NULL;
	pip->path_two = NULL;
	pip->cmd1 = NULL;
	pip->cmd2 = NULL;
	pip->pid1 = -1;
	pip->pid2 = -1;
	pip->paths = NULL;
}

int	ft_parse_args_errors(int argc, char **argv, char **envp)
{
	if (argc != 5)
	{
		write(1, "Error\n", 6);
		return (1);
	}
	if (!envp)
	{
		write(1, "Error : non environment\n", 24);
		return (1);
	}
	if (!argv[2] || !argv[2][0] || !argv[3] || !argv[3][0])
	{
	}
	return (0);
}

void	ft_clean_all(t_pip *pip)
{
	if (!pip)
		return ;
	if (pip->infile != -1)
		close(pip->infile);
	if (pip->outfile != -1)
		close(pip->outfile);
	if (pip->pipe_fd[0] != -1)
		close(pip->pipe_fd[0]);
	if (pip->pipe_fd[1] != -1)
		close(pip->pipe_fd[1]);
	if (pip->path_one)
		free(pip->path_one);
	if (pip->path_two)
		free(pip->path_two);
	if (pip->cmd1)
		ft_freedest(pip->cmd1);
	if (pip->cmd2)
		ft_freedest(pip->cmd2);
	if (pip->paths)
		ft_freedest(pip->paths);
	if (pip)
		free(pip);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	if (!s)
	{
		return ;
	}
	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}
