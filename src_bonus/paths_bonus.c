/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncrivell <ncrivell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 16:10:04 by ncrivell          #+#    #+#             */
/*   Updated: 2025/03/17 17:33:55 by ncrivell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "pipex.h"
#include "pipexbonus.h"

char	*ft_extract_path_cmd_bonus(char **paths, char *cmd)
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

char	**ft_extract_paths_bonus(char **envp)
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

char	*ft_handle_absolute_path_bonus(char *cmd)
{
	if (access(cmd, F_OK | X_OK) == 0)
		return (ft_strdup(cmd));
	ft_putstr_fd(cmd, 2);
	write(2, ": No such file or directory\n", 28);
	return (NULL);
}

char	*ft_find_path_bonus(char **envp, char *cmd, t_pip_b *pip)
{
	char	**paths;
	char	*path_cmd;

	if (pip->infile == 13351)
		return (NULL);
	if (cmd && ft_strchr(cmd, '/'))
		ft_handle_absolute_path_bonus(cmd);
	paths = ft_extract_paths_bonus(envp);
	if (!paths)
	{
		perror("Error extract_paths");
		return (NULL);
	}
	path_cmd = ft_extract_path_cmd_bonus(paths, cmd);
	ft_freedest(paths);
	if (!path_cmd)
	{
		ft_putstr_fd(cmd, 2);
		write(2, ": command not found\n", 20);
		return (NULL);
	}
	return (path_cmd);
}
