/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 13:33:59 by hnagasak          #+#    #+#             */
/*   Updated: 2023/05/14 16:49:40 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*us1;
	const unsigned char	*us2;
	size_t				len;

	us1 = (unsigned char *)s1;
	us2 = (unsigned char *)s2;
	len = 1;
	while (len <= n)
	{
		if (*us1 != *us2)
			return (*us1 - *us2);
		us1++;
		us2++;
		len++;
	}
	return (0);
}
