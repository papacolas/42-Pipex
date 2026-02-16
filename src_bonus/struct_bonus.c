/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncrivell <ncrivell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 16:05:21 by ncrivell          #+#    #+#             */
/*   Updated: 2025/03/17 13:14:47 by ncrivell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "pipex.h"
#include "pipexbonus.h"

void	ft_utils_mallocs_struct(t_pip_b *pip)
{
	ft_clean_all_bonus(pip);
	perror("Error malloc");
	exit(1);
}

void	ft_mallocs_struct(t_pip_b *pip, int cmd_number)
{
	int	i;

	pip->pipes_fd = malloc(sizeof(int *) * (cmd_number - 1));
	if (!pip->pipes_fd)
		ft_utils_mallocs_struct(pip);
	pip->cmd_paths = malloc(sizeof(char *) * cmd_number);
	if (!pip->cmd_paths)
		ft_utils_mallocs_struct(pip);
	pip->cmds = malloc(sizeof(char **) * cmd_number);
	if (!pip->cmds)
		ft_utils_mallocs_struct(pip);
	pip->pids = malloc(sizeof(pid_t) * cmd_number);
	if (!pip->pids)
		ft_utils_mallocs_struct(pip);
	i = 0;
	while (i < cmd_number - 1)
	{
		pip->pipes_fd[i] = malloc(sizeof(int) * 2);
		if (!pip->pipes_fd[i])
			ft_utils_mallocs_struct(pip);
		pip->pipes_fd[i][0] = -1;
		pip->pipes_fd[i][1] = -1;
		i++;
	}
}

void	ft_init_struct_bonus(t_pip_b *pip, int cmd_number)
{
	int	i;

	pip->infile = -1;
	pip->outfile = -1;
	pip->cmd_number = cmd_number;
	ft_mallocs_struct(pip, cmd_number);
	i = 0;
	while (i < cmd_number)
	{
		pip->cmd_paths[i] = NULL;
		pip->cmds[i] = NULL;
		pip->pids[i] = -1;
		i++;
	}
	pip->paths = NULL;
	pip->heredoc_or_not = 0;
	pip->delimiter = NULL;
}
