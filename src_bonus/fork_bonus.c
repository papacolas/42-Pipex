/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncrivell <ncrivell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 16:07:56 by ncrivell          #+#    #+#             */
/*   Updated: 2025/03/17 18:47:41 by ncrivell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "pipex.h"
#include "pipexbonus.h"

void	ft_handle_error_acces(t_pip_b *pip, int i)
{
	if (i == 0 && pip->infile == -421)
	{
		pip->infile = -1;
		ft_clean_all_bonus(pip);
		exit(1);
	}
	if (pip->infile == -421)
	{
		pip->infile = open("/dev/null", O_RDONLY);
		if (pip->infile < 0)
		{
			perror("Error opening /dev/null");
			pip->infile = -1;
			ft_clean_all_bonus(pip);
			exit(1);
		}
	}
}

void	ft_execute_child(t_pip_b *pip, char **envp, int i)
{
	ft_handle_error_acces(pip, i);
	ft_dup_childs(pip, i);
	if (!pip->cmd_paths[i])
	{
		if (!(i == 0 && pip->infile == -421))
		{
			if (pip->cmds[i] && pip->cmds[i][0])
			{
				ft_putstr_fd(pip->cmds[i][0], 2);
				ft_putstr_fd(": command not found\n", 2);
			}
			else
				ft_putstr_fd(": command not found\n", 2);
		}
		get_next_line(-1);
		ft_clean_all_bonus(pip);
		exit(127);
	}
	execve(pip->cmd_paths[i], pip->cmds[i], envp);
	perror("Error execve");
	get_next_line(-1);
	ft_clean_all_bonus(pip);
	exit(126);
}

void	ft_creating_childs_process(t_pip_b *pip, char **envp)
{
	int	i;

	i = 0;
	while (i < pip->cmd_number)
	{
		pip->pids[i] = fork();
		if (pip->pids[i] == -1)
		{
			ft_clean_all_bonus(pip);
			perror("Error fork");
			exit(1);
		}
		if (pip->pids[i] == 0)
			ft_execute_child(pip, envp, i);
		i++;
	}
}

void	ft_fork_and_execute_bonus(t_pip_b *pip, char **envp)
{
	int	i;
	int	j;

	ft_creating_childs_process(pip, envp);
	j = 0;
	while (j < pip->cmd_number - 1)
	{
		if (pip->pipes_fd[j][0] != -1)
			close(pip->pipes_fd[j][0]);
		if (pip->pipes_fd[j][1] != -1)
			close(pip->pipes_fd[j][1]);
		j++;
	}
	i = 0;
	while (i < pip->cmd_number)
	{
		waitpid(pip->pids[i], NULL, 0);
		i++;
	}
}
