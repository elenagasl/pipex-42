/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elengarc <elengarc@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 19:19:27 by elengarc          #+#    #+#             */
/*   Updated: 2025/05/06 19:19:29 by elengarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include "libft/libft.h"
# include <errno.h> 
# include <string.h>

// Estructura para cada comando
typedef struct s_cmd
{
	char	*path;
	char	**cmd;
	char	**env;
}	t_cmd;

int		pipex(int fd_in, int fd_out, t_cmd *cmd1, t_cmd *cmd2);
void	ft_proceso_hijo_1(int fd_in, int *fd, t_cmd *cmd1);
void	ft_proceso_hijo_2(int fd_out, int *fd, t_cmd *cmd2);
void	ft_free_cmd(t_cmd *cmd);
char	*ft_extract_path(char *cmd, char **envp);
char	*check_path_cmd(char **dirs, char *cmd);
t_cmd	manage_arguments(char *argv, char **envp);
char	**ft_split_shell(const char *s);
void	ft_free_split(char **arr);
int		ft_error_argn(void);
int		ft_error_file(char *file);
void	ft_error_path(char *cmd);
void	ft_error_pipe(void);
void	ft_error_pid(void);
void	ft_error_red(void);
void	ft_error_close(void);
int		ft_error_file_out(char *file);
void	ft_error_cmd(void);
void	ft_cmd_error(t_cmd *cmd);
void	ft_error_cmd_empty(void);
size_t	ft_strlen(const char *s);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

#endif
