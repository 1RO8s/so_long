/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:28:30 by hnagasak          #+#    #+#             */
/*   Updated: 2023/07/14 09:41:52 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_count_hex_digit(unsigned int num)
{
	int				digit;
	unsigned int	n;

	digit = 1;
	n = num / 16;
	while (n != 0 && digit++)
		n = n / 16;
	return (digit);
}

char	ft_get_hex_base(unsigned int n, int isUpper)
{
	if (0 <= n && n <= 9)
		return ('0' + n);
	else if (10 <= n && n < 16 && isUpper)
		return ('A' + (n - 10));
	else if (10 <= n && n < 16 && !isUpper)
		return ('a' + (n - 10));
	else
		return (0);
}

static char	*ft_get_hex_str(char *str, unsigned int n, int len, int isUpper)
{
	if (0 <= n && n < 16)
		*str = ft_get_hex_base(n, isUpper);
	else if (16 <= n)
	{
		ft_get_hex_str(str, n / 16, len - 1, isUpper);
		*(str + len - 1) = ft_get_hex_base(n % 16, isUpper);
	}
	return (str);
}

int	ft_puthex(unsigned int num, int isUpper)
{
	char	*str;
	int		len;

	len = ft_count_hex_digit(num);
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (-1);
	str = ft_get_hex_str(str, num, len, isUpper);
	ft_putstr(str);
	free(str);
	return (len);
}
