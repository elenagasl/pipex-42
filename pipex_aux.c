/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elengarc <elengarc@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:58:59 by elengarc          #+#    #+#             */
/*   Updated: 2025/05/06 18:59:01 by elengarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_extract_path(char *cmd, char **envp)
{
	char	**dirs;
	int		i;

	if (!cmd || !envp)
		return (NULL);
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
		return (NULL);
	dirs = ft_split(envp[i] + 5, ':');
	if (!dirs)
		return (NULL);
	return (check_path_cmd(dirs, cmd));
}

char	*check_path_cmd(char **dirs, char *cmd)
{
	int		i;
	char	*tmp;
	char	*full;

	if (!dirs || !cmd)
		return (NULL);
	i = 0;
	while (dirs[i])
	{
		tmp = ft_strjoin(dirs[i], "/");
		if (!tmp)
			return (ft_free_split(dirs), NULL);
		full = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!full)
			return (ft_free_split(dirs), NULL);
		if (access(full, X_OK) == 0)
			return (ft_free_split(dirs), full);
		free(full);
		i++;
	}
	ft_free_split(dirs);
	return (NULL);
}

void	ft_free_split(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	ft_free_cmd(t_cmd *cmd)
{
	if (cmd->cmd)
		ft_free_split(cmd->cmd);
	if (cmd->path)
		free(cmd->path);
}

void	ft_error_red(void)
{
	perror("dup2");
	exit(127);
}
