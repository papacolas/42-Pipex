/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncrivell <ncrivell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:27:37 by ncrivell          #+#    #+#             */
/*   Updated: 2025/03/17 19:08:12 by ncrivell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "pipex.h"
#include "pipexbonus.h"

int	ft_parse_args_errors_bonus(int argc, char **argv, char **envp)
{
	int	i;
	int	heredoc;

	heredoc = 0;
	if (argc < 5 || !envp || !envp[0])
	{
		if (argc < 5)
			write(1, "Error\n", 6);
		if (!envp || !envp[0])
			write(1, "Error : non environment\n", 24);
		return (1);
	}
	if (argc >= 6 && !ft_strncmp(argv[1], "here_doc", 9))
		heredoc = 1;
	i = 2;
	while (i < argc - 1)
	{
		if (!argv[i] || !argv[i][0])
		{
			if (i > (2 + heredoc) && i < argc - 2)
				write(2, "syntax error near unexpected token \"\"\n", 38);
		}
		i++;
	}
	return (0);
}

void	ft_split_cmds_bonus(t_pip_b *pip, char **argv, char **envp)
{
	int	i;

	i = 0;
	while (i < pip->cmd_number)
	{
		pip->cmds[i] = ft_split(argv[i + 2 + pip->heredoc_or_not], ' ');
		if (!pip->cmds[i])
		{
			ft_clean_all_bonus(pip);
			perror("Error split");
			exit(1);
		}
		if (!pip->cmds[i][0] || pip->cmds[i][0][0] == '\0')
		{
			pip->cmd_paths[i] = NULL;
		}
		else
		{
			pip->cmd_paths[i] = ft_find_path_bonus(envp, pip->cmds[i][0], pip);
		}
		i++;
	}
}

void	ft_open_input_file(t_pip_b *pip, char *filename)
{
	if (access(filename, F_OK) == 0 && access(filename, R_OK) != 0)
	{
		ft_putstr_fd(filename, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		pip->infile = -421;
		return ;
	}
	pip->infile = open(filename, O_RDONLY);
	if (pip->infile == -1)
	{
		ft_putstr_fd(filename, 2);
		ft_putstr_fd(": ", 2);
		perror("");
		pip->infile = open("/dev/null", O_RDONLY);
		if (pip->infile < 0)
		{
			perror("Error opening /dev/null");
			exit(1);
		}
	}
}

void	ft_open_output_file(t_pip_b *pip, char *filename)
{
	pip->outfile = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pip->outfile == -1)
	{
		ft_clean_all_bonus(pip);
		ft_putstr_fd(filename, 2);
		ft_putstr_fd(": ", 2);
		perror("");
		exit(1);
	}
}

void	ft_open_files_bonus(t_pip_b *pip, char **argv, int argc)
{
	ft_open_input_file(pip, argv[1]);
	ft_open_output_file(pip, argv[argc - 1]);
}
