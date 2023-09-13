/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:39:08 by hnagasak          #+#    #+#             */
/*   Updated: 2023/05/18 03:35:13 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	count_splited_arr(char const *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		while (*s == c)
			++s;
		if (*s)
		{
			++count;
			while (*s && *s != c)
				++s;
		}
	}
	return (count);
}

char	**free_all(char **result, size_t i)
{
	while (i > 0)
		free(result[--i]);
	free(result);
	return (NULL);
}

char	**set_splited_str(char **result, size_t i, char const *s,
		char const *start)
{
	result[i] = malloc(s - start + 1);
	if (!result[i])
		return (free_all(result, i));
	ft_strlcpy(result[i], start, s - start + 1);
	return (result);
}

char	**ft_split(char const *s, char c)
{
	size_t		words;
	char		**result;
	size_t		i;
	const char	*start;

	if (!s)
		return (NULL);
	words = count_splited_arr(s, c);
	result = malloc((words + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	i = 0;
	while (i < words)
	{
		while (*s == c)
			++s;
		start = s;
		while (*s && *s != c)
			++s;
		if (set_splited_str(result, i, s, start) == NULL)
			return (NULL);
		i++;
	}
	return (result);
}
