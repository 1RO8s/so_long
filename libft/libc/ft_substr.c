/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:01:22 by hnagasak          #+#    #+#             */
/*   Updated: 2023/05/20 00:04:42 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*substr;
	const char	*sub_start;

	if (ft_strlen(s) < start + 1)
		return ("");
	sub_start = s + start;
	substr = ft_calloc(len + 1, sizeof(char));
	if (substr != NULL)
		ft_strlcpy(substr, (char *)sub_start, len + 1);
	return ((char *)substr);
}
