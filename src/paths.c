/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncrivell <ncrivell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:04:47 by ncrivell          #+#    #+#             */
/*   Updated: 2025/03/17 20:01:14 by ncrivell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "pipex.h"

void	ft_cmd_path(t_pip *pip, char **argv, char **envp)
{
	pip->cmd1 = ft_split(argv[2], ' ');
	pip->cmd2 = ft_split(argv[3], ' ');
	if (!pip->cmd1 || !pip->cmd2)
	{
		ft_clean_all(pip);
		perror("Error split");
		exit(1);
	}
	if (!pip->cmd1[0] || pip->cmd1[0][0] == '\0')
		pip->path_one = NULL;
	else
		pip->path_one = ft_find_path(envp, pip->cmd1[0], pip);
	if (!pip->cmd2[0] || pip->cmd2[0][0] == '\0')
		pip->path_two = NULL;
	else
		pip->path_two = ft_find_path(envp, pip->cmd2[0], pip);
	if (pipe(pip->pipe_fd) == -1)
	{
		ft_clean_all(pip);
		perror("Error pipe");
		exit(1);
	}
}

char	**ft_extract_paths(char **envp)
{
	int		i;
	char	**paths;

	i = 0;
	paths = NULL;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			paths = ft_split(envp[i] + 5, ':');
			if (!paths)
			{
				perror("Error split");
				return (NULL);
			}
			break ;
		}
		i++;
	}
	if (!envp[i])
	{
		write(1, "Error path\n", 11);
		return (NULL);
	}
	return (paths);
}

char	*ft_extract_path_cmd(char **paths, char *cmd)
{
	int		i;
	char	*path_cmd;

	path_cmd = NULL;
	i = 0;
	while (paths[i])
	{
		path_cmd = ft_strjoin(paths[i], "/", cmd);
		if (!path_cmd)
		{
			return (NULL);
		}
		if (access(path_cmd, F_OK | X_OK) == 0)
			return (path_cmd);
		free(path_cmd);
		i++;
	}
	return (NULL);
}

char	*ft_handle_absolute_path(char *cmd)
{
	if (access(cmd, F_OK | X_OK) == 0)
		return (ft_strdup(cmd));
	ft_putstr_fd(cmd, 2);
	write(2, ": No such file or directory\n", 28);
	return (NULL);
}

char	*ft_find_path(char **envp, char *cmd, t_pip *pip)
{
	char	**paths;
	char	*path_cmd;

	if (pip->infile == 15654)
		return (NULL);
	if (!cmd || cmd[0] == '\0')
		return (NULL);
	if (cmd && ft_strchr(cmd, '/'))
		return (ft_handle_absolute_path(cmd));
	paths = ft_extract_paths(envp);
	if (!paths)
	{
		perror("Error extract_paths");
		return (NULL);
	}
	path_cmd = ft_extract_path_cmd(paths, cmd);
	ft_freedest(paths);
	if (!path_cmd)
	{
		ft_putstr_fd(cmd, 2);
		write(2, ": command not found\n", 20);
		return (NULL);
	}
	return (path_cmd);
}
