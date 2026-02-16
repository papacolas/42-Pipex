/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncrivell <ncrivell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:35:41 by ncrivell          #+#    #+#             */
/*   Updated: 2025/03/10 16:24:14 by ncrivell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "pipex.h"
#include "pipexbonus.h"

void	ft_close_descriptors(t_pip_b *pip)
{
	int	i;

	i = 0;
	while (i < pip->cmd_number - 1)
	{
		if (pip->pipes_fd[i][0] != -1)
			close(pip->pipes_fd[i][0]);
		if (pip->pipes_fd[i][1] != -1)
			close(pip->pipes_fd[i][1]);
		i++;
	}
	if (pip->infile != -1)
		close(pip->infile);
	if (pip->outfile != -1)
		close(pip->outfile);
}

void	ft_free_tableaux(t_pip_b *pip)
{
	int	i;

	i = 0;
	while (i < pip->cmd_number)
	{
		if (pip->cmd_paths[i])
			free(pip->cmd_paths[i]);
		if (pip->cmds[i])
			ft_freedest(pip->cmds[i]);
		i++;
	}
	if (pip->cmd_paths)
		free(pip->cmd_paths);
	if (pip->cmds)
		free(pip->cmds);
	if (pip->pids)
		free(pip->pids);
}

void	ft_close_fork_child(t_pip_b *pip)
{
	int	j;

	if (pip->infile != -1)
		close(pip->infile);
	if (pip->outfile != -1)
		close(pip->outfile);
	j = 0;
	while (j < pip->cmd_number - 1)
	{
		if (pip->pipes_fd[j][0] != -1)
			close(pip->pipes_fd[j][0]);
		if (pip->pipes_fd[j][1] != -1)
			close(pip->pipes_fd[j][1]);
		j++;
	}
}

void	ft_clean_all_bonus(t_pip_b *pip)
{
	int	i;

	ft_close_descriptors(pip);
	ft_free_tableaux(pip);
	i = 0;
	while (i < pip->cmd_number -1)
	{
		if (pip->pipes_fd[i])
		{
			free(pip->pipes_fd[i]);
			pip->pipes_fd[i] = NULL;
		}
		i++;
	}
	if (pip->pipes_fd)
		free(pip->pipes_fd);
	if (pip->paths)
		ft_freedest(pip->paths);
	if (pip)
		free(pip);
}

void	ft_dup_childs(t_pip_b *pip, int i)
{
	if (i == 0)
		dup2(pip->infile, 0);
	else
		dup2(pip->pipes_fd[i - 1][0], 0);
	if (i == pip->cmd_number - 1)
		dup2(pip->outfile, 1);
	else
		dup2(pip->pipes_fd[i][1], 1);
	ft_close_fork_child(pip);
}
