/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncrivell <ncrivell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:06:32 by ncrivell          #+#    #+#             */
/*   Updated: 2025/03/17 18:56:22 by ncrivell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "pipex.h"
#include "pipexbonus.h"

void	ft_create_pipes_bonus(t_pip_b *pip)
{
	int	i;

	i = 0;
	while (i < pip->cmd_number -1)
	{
		if (pipe(pip->pipes_fd[i]) == -1)
		{
			ft_clean_all_bonus(pip);
			perror("Error pipe");
			exit(1);
		}
		i++;
	}
}

void	ft_check_heredoc(t_pip_b *pip, int argc, char **argv)
{
	int	cmd_number;
	int	is_heredoc;

	is_heredoc = ft_is_heredoc(pip, argc, argv);
	cmd_number = argc - 3;
	if (is_heredoc)
		cmd_number = argc - 3 - 1;
	ft_init_struct_bonus(pip, cmd_number);
	if (is_heredoc)
	{
		pip->heredoc_or_not = 1;
		ft_heredoc(pip, argv[2]);
		pip->outfile = open(argv[argc - 1], O_WRONLY | O_CREAT
				| O_APPEND, 0644);
		if (pip->outfile == -1)
		{
			unlink(".heredoc_temp");
			ft_clean_all_bonus(pip);
			perror("Error opening output file");
			exit(1);
		}
	}
	else
		ft_open_files_bonus(pip, argv, argc);
}

int	main(int argc, char **argv, char **envp)
{
	t_pip_b	*pip;
	int		error;

	error = ft_parse_args_errors_bonus(argc, argv, envp);
	if (error)
		return (1);
	pip = malloc(sizeof(t_pip_b));
	if (!pip)
	{
		perror("Error malloc");
		return (1);
	}
	ft_check_heredoc(pip, argc, argv);
	ft_split_cmds_bonus(pip, argv, envp);
	ft_create_pipes_bonus(pip);
	ft_fork_and_execute_bonus(pip, envp);
	ft_clean_all_bonus(pip);
	get_next_line(-1);
	return (0);
}
