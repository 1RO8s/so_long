/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 03:22:43 by hnagasak          #+#    #+#             */
/*   Updated: 2023/01/15 00:42:08 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <ctype.h>

int	ft_isascii(int c)
{
	return (0 <= c && c <= 127);
}

// int	main(void)
// {
// 	int c;
// 	c = -1;
// 	printf("%d -> %d, %d\n",c , ft_isascii(c), isascii(c));
// 	c = 0;
// 	printf("%d -> %d, %d\n",c , ft_isascii(c), isascii(c));
// 	c = 1;
// 	printf("%d -> %d, %d\n",c , ft_isascii(c), isascii(c));
// 	c = 127;
// 	printf("%d -> %d, %d\n",c , ft_isascii(c), isascii(c));
// 	c = 200;
// 	printf("%d -> %d, %d\n",c , ft_isascii(c), isascii(c));
// }
