/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 16:28:46 by hnagasak          #+#    #+#             */
/*   Updated: 2023/09/13 19:05:31 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../libc/libft.h"
# include <limits.h>
# include <stdarg.h>
# include <stdio.h>

# define UPPER 1
# define LOWER 0

char	ft_get_hex_base(unsigned int n, int isUpper);
int		ft_puthex(unsigned int num, int isUpper);
int		ft_putstr(char *str);
int		ft_printf(const char *format, ...);
int		ft_putstr(char *str);
int		ft_putptr(uintptr_t ptr);
int		ft_putuint(unsigned int num);

#endif