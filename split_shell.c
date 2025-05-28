/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elengarc <elengarc@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:52:37 by elengarc          #+#    #+#             */
/*   Updated: 2025/05/08 12:52:38 by elengarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	word_len(const char *s)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (s[i])
	{
		if (!quote && (s[i] == '"' || s[i] == '\''))
			quote = s[i];
		else if (quote && s[i] == quote)
			quote = 0;
		else if (!quote && s[i] == ' ')
			break ;
		i++;
	}
	return (i);
}

static int	count_words(const char *s)
{
	int		count;
	int		i;
	char	quote;

	count = 0;
	i = 0;
	quote = 0;
	while (s[i])
	{
		while (s[i] == ' ')
			i++;
		if (s[i])
		{
			count++;
			while (s[i] && (quote || s[i] != ' '))
			{
				if (!quote && (s[i] == '"' || s[i] == '\''))
					quote = s[i];
				else if (quote && s[i] == quote)
					quote = 0;
				i++;
			}
		}
	}
	return (count);
}

static char	*extract_word(const char *s, int len)
{
	if ((s[0] == '"' || s[0] == '\'') && len >= 2 && s[len - 1] == s[0])
		return (ft_substr(s + 1, 0, len - 2));
	return (ft_substr(s, 0, len));
}

static void	free_all(char **arr, int i)
{
	while (--i >= 0)
		free(arr[i]);
	free(arr);
}

char	**ft_split_shell(const char *s)
{
	char	**res;
	int		words;
	int		i;
	int		len;

	if (!s)
		return (NULL);
	words = count_words(s);
	res = malloc(sizeof(char *) * (words + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (*s && i < words)
	{
		while (*s == ' ')
			s++;
		len = word_len(s);
		res[i] = extract_word(s, len);
		if (!res[i])
			return (free_all(res, i), NULL);
		s += len;
		i++;
	}
	res[i] = NULL;
	return (res);
}
