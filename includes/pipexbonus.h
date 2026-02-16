/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipexbonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncrivell <ncrivell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:04:35 by ncrivell          #+#    #+#             */
/*   Updated: 2025/03/17 18:55:03 by ncrivell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEXBONUS_H
# define PIPEXBONUS_H
# define BUFFER_SIZE 1024

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <string.h>
# include <stdio.h>

typedef struct s_pip_b
{
	int		infile;
	int		outfile;
	int		**pipes_fd;
	char	**cmd_paths;
	char	***cmds;
	char	**paths;
	int		cmd_number;
	pid_t	*pids;
	int		heredoc_or_not;
	char	*delimiter;
}	t_pip_b;

char	*ft_extract_path_cmd_bonus(char **paths, char *cmd);
char	**ft_extract_paths_bonus(char **envp);
char	*ft_find_path_bonus(char **envp, char *cmd, t_pip_b *pip);
void	ft_split_cmds_bonus(t_pip_b *pip, char **argv, char **envp);
void	ft_open_files_bonus(t_pip_b *pip, char **argv, int argc);
void	ft_init_struct_bonus(t_pip_b *pip, int cmd_number);
void	ft_create_pipes_bonus(t_pip_b *pip);
void	ft_clean_all_bonus(t_pip_b *pip);
void	ft_fork_and_execute_bonus(t_pip_b *pip, char **envp);
int		ft_parse_args_errors_bonus(int argc, char **argv, char **envp);
char	*ft_explore_text(char *principal_buff, int fd);
char	*ft_create_line(char *principal_buff);
char	*ft_new_buff(char *principal_buff);
char	*freebuff(char **principal_buff);
char	*get_next_line(int fd);
int		ft_is_heredoc(t_pip_b *pip, int argc, char **argv);
void	ft_heredoc(t_pip_b *pip, char *delimiter);

char	*ft_strjoin_gnl(char const *s1, char const *s2);

void	ft_check_heredoc(t_pip_b *pip, int argc, char **argv);
void	ft_utils_mallocs_struct(t_pip_b *pip);
void	ft_mallocs_struct(t_pip_b *pip, int cmd_number);

void	ft_close_descriptors(t_pip_b *pip);
void	ft_free_tableaux(t_pip_b *pip);
void	ft_close_fork_child(t_pip_b *pip);
void	ft_dup_childs(t_pip_b *pip, int i);
void	ft_creating_childs_process(t_pip_b *pip, char **envp);
void	ft_read_heredoc(int temp_fd, int size_del, char *delimiter);
void	ft_putstr_fd(char *s, int fd);
char	*ft_handle_absolute_path_bonus(char *cmd);
void	ft_execute_child(t_pip_b *pip, char **envp, int i);
void	ft_handle_error_acces(t_pip_b *pip, int i);

void	ft_open_input_file(t_pip_b *pip, char *filename);
void	ft_open_output_file(t_pip_b *pip, char *filename);
#endif
