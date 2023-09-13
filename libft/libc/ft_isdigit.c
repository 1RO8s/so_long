/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 03:22:43 by hnagasak          #+#    #+#             */
/*   Updated: 2023/01/13 03:27:33 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <ctype.h>

int	ft_isdigit(int c)
{
	return ('0' <= c && c <= '9');
}

// int main(void)
// {
// 	printf("%d\n",ft_isdigit('0'));
// 	printf("%d\n",isdigit('0'));
// 	printf("%d\n",ft_isdigit('9'));
// 	printf("%d\n",isdigit('9'));
// 	printf("%d\n",ft_isdigit('_'));
// 	printf("%d\n",isdigit('_'));
// }
