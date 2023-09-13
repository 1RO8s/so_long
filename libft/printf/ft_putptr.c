/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:44:16 by hnagasak          #+#    #+#             */
/*   Updated: 2023/07/14 09:45:20 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_count_ptr_digit(uintptr_t num)
{
	int			digit;
	uintptr_t	n;

	digit = 1;
	n = num / 16;
	while (n != 0 && digit++)
		n = n / 16;
	return (digit);
}

char	*ft_get_ptr_str(char *str, uintptr_t n, int len)
{
	if (0 <= n && n < 16)
		*str = ft_get_hex_base(n, 0);
	else if (16 <= n)
	{
		ft_get_ptr_str(str, n / 16, len - 1);
		*(str + len - 1) = ft_get_hex_base(n % 16, 0);
	}
	return (str);
}

int	ft_putptr(uintptr_t ptr)
{
	char	*str;
	int		len;

	len = ft_count_ptr_digit(ptr);
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (-1);
	str = ft_get_ptr_str(str, ptr, len);
	ft_putstr("0x");
	ft_putstr(str);
	free(str);
	return (len + 2);
}
