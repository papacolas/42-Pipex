/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncrivell <ncrivell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 15:09:58 by ncrivell          #+#    #+#             */
/*   Updated: 2025/03/14 17:35:20 by ncrivell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "pipex.h"
#include "pipexbonus.h"

int	ft_is_heredoc(t_pip_b *pip, int argc, char **argv)
{
	if (argc >= 6 && !ft_strncmp(argv[1], "here_doc", 9))
	{
		pip->heredoc_or_not = 1;
		pip->delimiter = argv[2];
		return (1);
	}
	pip->heredoc_or_not = 0;
	pip->delimiter = NULL;
	return (0);
}

void	ft_read_heredoc(int temp_fd, int size_del, char *delimiter)
{
	char	*line;

	write(1, "heredoc> ", 9);
	line = get_next_line(0);
	while (line != NULL)
	{
		if (!ft_strncmp(line, delimiter, size_del) && (line[size_del] == '\n'
				|| line[size_del] == '\0'))
		{
			free(line);
			break ;
		}
		write(temp_fd, line, ft_strlen(line));
		free(line);
		write(1, "heredoc> ", 9);
		line = get_next_line(0);
	}
}

void	ft_heredoc(t_pip_b *pip, char *delimiter)
{
	int		temp_fd;
	int		size_del;

	temp_fd = open(".heredoc_temp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (temp_fd < 0)
	{
		ft_clean_all_bonus(pip);
		perror("Error creating file temp");
		exit(1);
	}
	size_del = ft_strlen(delimiter);
	ft_read_heredoc(temp_fd, size_del, delimiter);
	close(temp_fd);
	pip->infile = open(".heredoc_temp", O_RDONLY);
	if (pip->infile < 0)
	{
		unlink(".heredoc_temp");
		perror("Error opening temp file");
		ft_clean_all_bonus(pip);
		exit(1);
	}
}
