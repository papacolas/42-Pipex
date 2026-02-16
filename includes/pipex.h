/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncrivell <ncrivell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:16:16 by ncrivell          #+#    #+#             */
/*   Updated: 2025/03/17 17:31:49 by ncrivell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <string.h>
# include <stdio.h>

typedef struct s_pip
{
	int		infile;
	int		outfile;
	int		pipe_fd[2];
	char	*path_one;
	char	*path_two;
	char	**cmd1;
	char	**cmd2;
	char	**paths;
	char	*path_cmd;
	pid_t	pid1;
	pid_t	pid2;
}	t_pip;

void		ft_init(t_pip *pip, char **argv, char **envp);
char		*ft_find_path(char **envp, char *cmd, t_pip *pip);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		**ft_split(char const *s, char c);
void		ft_freedest(char **dest);
char		*ft_strsplt(char const *s, int debut, int lenstr);
int			ft_countdel(char const *s, char c);
char		*ft_strjoin(char const *s1, char const *s2, char const *s3);
size_t		ft_strlen(const char *str);
void		ft_open_files(t_pip *pip, char **argv);
void		ft_init_struct(t_pip *pip);
void		ft_cmd_path(t_pip *pip, char **argv, char **envp);
void		ft_fork_one(t_pip *pip, char **envp);
void		ft_fork_two(t_pip *pip, char **envp);
char		**ft_extract_paths(char **envp);
char		*ft_extract_path_cmd(char **paths, char *cmd);
int			ft_parse_args_errors(int argc, char **argv, char **envp);
void		ft_clean_all(t_pip *pip);
void		ft_putstr_fd(char *s, int fd);
char		*ft_strchr(const char *s, int c);
char		*ft_strdup(const char *s);
char		*ft_handle_absolute_path(char *cmd);
#endif
