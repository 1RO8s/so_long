/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 14:54:23 by hnagasak          #+#    #+#             */
/*   Updated: 2023/09/13 19:07:51 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr(int num)
{
	int	len;
	int	tmp;

	len = 1;
	if (num < 0)
		len++;
	tmp = num / 10;
	while (tmp != 0)
	{
		len++;
		tmp = tmp / 10;
	}
	ft_putnbr_fd(num, 1);
	return (len);
}

int	ft_putchar(char c)
{
	ft_putchar_fd(c, 1);
	return (1);
}

int	ft_putstr(char *str)
{
	if (str == NULL)
		return (ft_putstr("(null)"));
	ft_putstr_fd(str, 1);
	return (ft_strlen(str));
}

int	ft_print_specifier(char *c, va_list *args)
{
	int	length;

	length = 0;
	if (*c == 'c')
		length = ft_putchar((char)va_arg(*args, int));
	else if (*c == 's')
		length = ft_putstr(va_arg(*args, char *));
	else if (*c == 'p')
		length = ft_putptr(va_arg(*args, uintptr_t));
	else if (*c == 'd' || *c == 'i')
		length = ft_putnbr(va_arg(*args, int));
	else if (*c == 'u')
		length = ft_putuint(va_arg(*args, unsigned int));
	else if (*c == 'X')
		length = ft_puthex(va_arg(*args, unsigned int), UPPER);
	else if (*c == 'x')
		length = ft_puthex(va_arg(*args, unsigned int), LOWER);
	else if (*c == '%')
		length = ft_putchar('%');
	else
		length = ft_putchar(*c);
	return (length);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	char	*c;
	int		length;

	length = 0;
	c = (char *)format;
	va_start(args, format);
	while (*c != '\0')
	{
		if (*c == '%')
			length += ft_print_specifier(++c, &args);
		else
			length += ft_putchar(*c);
		c++;
	}
	return (length);
}
