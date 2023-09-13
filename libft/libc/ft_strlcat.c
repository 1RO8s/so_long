/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 18:44:38 by hnagasak          #+#    #+#             */
/*   Updated: 2023/05/21 15:11:23 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	char	*start;
	size_t	i;
	size_t	dstlen;

	if (dst == NULL)
		return (ft_strlen(src));
	dstlen = ft_strlen(dst);
	start = dst;
	while (*start != '\0')
		start++;
	i = 0;
	while (dstlen + i + 1 < dstsize && src[i] != '\0')
	{
		start[i] = src[i];
		i++;
	}
	start[i] = '\0';
	if (dstlen < dstsize)
		return (dstlen + ft_strlen(src));
	else
		return (dstsize + ft_strlen(src));
}
