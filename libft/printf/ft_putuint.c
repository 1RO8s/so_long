/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putuint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:50:12 by hnagasak          #+#    #+#             */
/*   Updated: 2023/07/14 09:51:02 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_count_uint_digit(unsigned int num)
{
	int				digit;
	unsigned int	n;

	digit = 1;
	n = num / 10;
	while (n != 0 && digit++)
		n = n / 10;
	return (digit);
}

static void	ft_ui2a(char *str, unsigned int n, int len)
{
	if (0 <= n && n < 10)
		*str = '0' + n;
	else if (10 <= n)
	{
		ft_ui2a(str, n / 10, len - 1);
		*(str + len - 1) = '0' + (n % 10);
	}
}

int	ft_putuint(unsigned int num)
{
	char	*result;
	int		len;

	len = ft_count_uint_digit(num);
	result = (char *)malloc((len + 1) * sizeof(char));
	if (!result)
		return (-1);
	ft_ui2a(result, num, len);
	ft_putstr(result);
	free(result);
	return (len);
}
