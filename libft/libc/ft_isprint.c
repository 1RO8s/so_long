/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 00:44:45 by hnagasak          #+#    #+#             */
/*   Updated: 2023/01/15 01:11:01 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <ctype.h>

int	ft_isprint(int c)
{
	return (' ' <= c && c <= '~');
}

// int	main(void)
// {
// 	int c;
// 	c = -1;
// 	printf("%d -> %d, %d\n", c, ft_isprint(c), isprint(c));
// 	c = 0;
// 	printf("%d -> %d, %d\n", c, ft_isprint(c), isprint(c));
// 	c = ' ';
// 	printf("%d -> %d, %d\n", c, ft_isprint(c), isprint(c));
// 	c = '~';
// 	printf("%d -> %d, %d\n", c, ft_isprint(c), isprint(c));
// 	c = 127;
// 	printf("%d -> %d, %d\n", c, ft_isprint(c), isprint(c));
// }
