/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elengarc <elengarc@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:32:53 by elengarc          #+#    #+#             */
/*   Updated: 2025/05/06 16:32:54 by elengarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static pid_t	fork1(t_cmd *cmd1, int *fd, int fd_in)
{
	pid_t	hijo1;

	if (cmd1->cmd && cmd1->path)
		hijo1 = fork();
	else
	{
		hijo1 = -2;
		close(fd[1]);
	}
	if (hijo1 == 0)
		ft_proceso_hijo_1(fd_in, fd, cmd1);
	else if (hijo1 == -1)
		ft_error_pid();
	return (hijo1);
}

static pid_t	fork2(t_cmd *cmd2, int *fd, int fd_out)
{
	pid_t	hijo2;

	if (cmd2->cmd && cmd2->path)
		hijo2 = fork();
	else
	{
		hijo2 = -2;
		close(fd[0]);
	}
	if (hijo2 == 0)
		ft_proceso_hijo_2(fd_out, fd, cmd2);
	else if (hijo2 == -1)
		ft_error_pid();
	return (hijo2);
}

void	ft_proceso_hijo_1(int fd_in, int *fd, t_cmd *cmd1)
{
	if (!cmd1 || !cmd1->path || !cmd1->cmd || !cmd1->env)
		ft_error_cmd();
	if (dup2(fd_in, 0) == -1)
		ft_error_red();
	if (dup2(fd[1], 1) == -1)
		ft_error_red();
	close(fd_in);
	close(fd[0]);
	close(fd[1]);
	execve(cmd1->path, cmd1->cmd, cmd1->env);
	ft_cmd_error(cmd1);
	exit(127);
}

void	ft_proceso_hijo_2(int fd_out, int *fd, t_cmd *cmd2)
{
	if (!cmd2 || !cmd2->path || !cmd2->cmd || !cmd2->env)
		ft_error_cmd();
	if (fd_out < 0 || dup2(fd[0], 0) == -1)
		ft_error_red();
	if (dup2(fd_out, 1) == -1)
		ft_error_red();
	close(fd_out);
	close(fd[0]);
	close(fd[1]);
	execve(cmd2->path, cmd2->cmd, cmd2->env);
	ft_cmd_error(cmd2);
	exit(127);
}

int	pipex(int fd_in, int fd_out, t_cmd *cmd1, t_cmd *cmd2)
{
	int		fd[2];
	pid_t	hijo1;
	pid_t	hijo2;

	if (pipe(fd) == -1)
		ft_error_pipe();
	hijo1 = fork1(cmd1, fd, fd_in);
	hijo2 = fork2(cmd2, fd, fd_out);
	if (hijo1 > 0)
	{
		close(fd[1]);
		waitpid(hijo1, NULL, 0);
	}
	if (hijo2 > 0)
	{
		close(fd[0]);
		waitpid(hijo2, NULL, 0);
	}
	ft_free_cmd(cmd1);
	ft_free_cmd(cmd2);
	return (0);
}
