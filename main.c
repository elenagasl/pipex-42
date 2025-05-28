/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elengarc <elengarc@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 13:31:27 by elengarc          #+#    #+#             */
/*   Updated: 2025/05/08 13:31:29 by elengarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_cmd	manage_arguments(char *argv, char **envp)
{
	t_cmd	cmd1;

	cmd1.cmd = ft_split_shell(argv);
	if (!cmd1.cmd || !cmd1.cmd[0])
		return (ft_error_cmd_empty(), cmd1.cmd = NULL,
			cmd1.path = NULL, cmd1.env = NULL, cmd1);
	cmd1.env = envp;
	cmd1.path = ft_extract_path(cmd1.cmd[0], envp);
	if (!cmd1.path)
		return (ft_error_path(cmd1.cmd[0]), cmd1.cmd = NULL,
			cmd1.env = NULL, cmd1);
	return (cmd1);
}

int	main(int argc, char **argv, char **envp)
{
	t_cmd	cmd1;
	t_cmd	cmd2;
	int		fd_in;
	int		fd_out;

	if (argc != 5)
		return (ft_error_argn());
	fd_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out == -1)
		return (ft_error_file_out(argv[4]));
	fd_in = open(argv[1], O_RDONLY);
	cmd1 = manage_arguments(argv[2], envp);
	cmd2 = manage_arguments(argv[3], envp);
	pipex(fd_in, fd_out, &cmd1, &cmd2);
	return (0);
}
