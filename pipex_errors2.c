/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_errors2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elengarc <elengarc@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 19:11:02 by elengarc          #+#    #+#             */
/*   Updated: 2025/05/06 19:11:04 by elengarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_error_close(void)
{
	perror("close");
	exit(EXIT_FAILURE);
}

void	ft_error_cmd(void)
{
	write(2, "Error: comando mal construido o vacío\n", 38);
	exit(127);
}

void	ft_cmd_error(t_cmd *cmd)
{
	const char	*msg;

	msg = strerror(errno);
	write(2, "zsh: ", 5);
	if (msg)
		write(2, msg, ft_strlen(msg));
	write(2, ": ", 2);
	if (cmd && cmd->cmd && cmd->cmd[0])
		write(2, cmd->cmd[0], ft_strlen(cmd->cmd[0]));
	write(2, "\n", 1);
	exit(127);
}

void	ft_error_path(char *cmd)
{
	write(2, "zsh: command not found: ", 25);
	write(2, cmd, ft_strlen(cmd));
	write(2, "\n", 1);
}

void	ft_error_cmd_empty(void)
{
	write(2, "zsh: permission denied: ", 25);
	write(2, "\n", 1);
}
