/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncrivell <ncrivell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:15:49 by ncrivell          #+#    #+#             */
/*   Updated: 2025/03/17 19:49:45 by ncrivell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "pipex.h"

void	ft_fork_two(t_pip *pip, char **envp)
{
	pip->pid2 = fork();
	if (pip->pid2 < 0)
	{
		ft_clean_all(pip);
		perror("Error fork");
		exit(1);
	}
	if (pip->pid2 == 0)
	{
		dup2(pip->pipe_fd[0], 0);
		dup2(pip->outfile, 1);
		close(pip->infile);
		close(pip->outfile);
		close(pip->pipe_fd[0]);
		close(pip->pipe_fd[1]);
		if (!pip->path_two)
		{
			ft_clean_all(pip);
			exit(127);
		}
		execve(pip->path_two, pip->cmd2, envp);
		ft_clean_all(pip);
		perror("Error");
		exit(126);
	}
}

void	ft_fork_one(t_pip *pip, char **envp)
{
	pip->pid1 = fork();
	if (pip->pid1 < 0)
	{
		ft_clean_all(pip);
		perror("Error fork");
		exit(1);
	}
	if (pip->pid1 == 0)
	{
		dup2(pip->infile, 0);
		dup2(pip->pipe_fd[1], 1);
		close(pip->infile);
		close(pip->outfile);
		close(pip->pipe_fd[0]);
		close(pip->pipe_fd[1]);
		if (!pip->path_one)
		{
			ft_clean_all(pip);
			exit(127);
		}
		execve(pip->path_one, pip->cmd1, envp);
		ft_clean_all(pip);
		perror("Error");
		exit(126);
	}
}

void	ft_open_files(t_pip *pip, char **argv)
{
	pip->infile = open(argv[1], O_RDONLY);
	if (pip->infile == -1)
	{
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd(": ", 2);
		perror("");
		pip->infile = open("/dev/null", O_RDONLY);
		if (pip->infile < 0)
		{
			perror("Error opening /dev/null");
			exit(1);
		}
	}
	pip->outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pip->outfile == -1)
	{
		ft_clean_all(pip);
		ft_putstr_fd(argv[4], 2);
		ft_putstr_fd(": ", 2);
		perror("");
		exit(1);
	}
}

void	ft_init(t_pip *pip, char **argv, char **envp)
{
	ft_open_files(pip, argv);
	ft_cmd_path(pip, argv, envp);
	ft_fork_one(pip, envp);
	ft_fork_two(pip, envp);
	if (pip->infile != -1)
		close(pip->infile);
	if (pip->outfile != -1)
		close(pip->outfile);
	if (pip->pipe_fd[0] != -1)
		close(pip->pipe_fd[0]);
	if (pip->pipe_fd[1] != -1)
		close(pip->pipe_fd[1]);
	waitpid(pip->pid1, NULL, 0);
	waitpid(pip->pid2, NULL, 0);
	if (pip->path_one)
		free(pip->path_one);
	if (pip->path_two)
		free(pip->path_two);
	if (pip->cmd1)
		ft_freedest(pip->cmd1);
	if (pip->cmd2)
		ft_freedest(pip->cmd2);
}

int	main(int argc, char **argv, char **envp)
{
	t_pip	*pip;
	int		error;

	error = ft_parse_args_errors(argc, argv, envp);
	if (error)
		return (1);
	pip = malloc(sizeof(t_pip));
	if (!pip)
	{
		perror("Error malloc");
		return (1);
	}
	ft_init_struct(pip);
	ft_init(pip, argv, envp);
	free(pip);
	return (0);
}
