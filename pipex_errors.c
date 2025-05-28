/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elengarc <elengarc@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 19:04:04 by elengarc          #+#    #+#             */
/*   Updated: 2025/05/06 19:04:06 by elengarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_error_argn(void)
{
	write(2, "Error: Número incorrecto de argumentos.\n", 41);
	return (1);
}

int	ft_error_file(char *file)
{
	const char	*msg;

	msg = strerror(errno);
	write(2, "zsh: ", 5);
	if (msg)
		write(2, msg, ft_strlen(msg));
	write(2, ": ", 2);
	if (file)
		write(2, file, ft_strlen(file));
	write(2, "\n", 1);
	return (1);
}

int	ft_error_file_out(char *file)
{
	const char	*msg;

	msg = strerror(errno);
	write(2, "zsh: ", 5);
	if (msg)
		write(2, msg, ft_strlen(msg));
	write(2, ": ", 2);
	if (file)
		write(2, file, ft_strlen(file));
	write(2, "\n", 1);
	return (1);
}

void	ft_error_pipe(void)
{
	perror("pipe");
	exit(EXIT_FAILURE);
}

void	ft_error_pid(void)
{
	perror("fork");
	exit(127);
}
