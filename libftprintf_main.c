/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf_main.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:53:24 by khorike           #+#    #+#             */
/*   Updated: 2023/06/14 13:58:53 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

ssize_t	ft_put_pointer(unsigned long long n)
{
	ssize_t		num;
	const char	ptr[] = "0123456789abcdef";

	num = 0;
	if (n >= 16)
		num += ft_put_pointer(n / 16);
	num += write(1, &ptr[n % 16], 1);
	return (num);
}

static ssize_t	ft_all_put(va_list ap, char c)
{
	ssize_t	count;

	if (c == 'c')
		count = ft_putchar((char)va_arg(ap, int));
	else if (c == 's')
		count = ft_putstr(va_arg(ap, char *));
	else if (c == 'd' || c == 'i')
		count = ft_putnbr(va_arg(ap, int));
	else if (c == 'p')
	{
		count = ft_putstr("0x");
		count += ft_put_pointer(va_arg(ap, unsigned long long));
	}
	else if (c == 'u')
		count = ft_put_unsigned_nbr(va_arg(ap, unsigned int));
	else if (c == 'x')
		count = ft_putnbr_base(va_arg(ap, unsigned int), 0);
	else if (c == 'X')
		count = ft_putnbr_base(va_arg(ap, unsigned int), 1);
	if (c == '%')
		count = ft_putchar('%');
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list		ap;
	ssize_t		count;
	size_t		i;

	va_start(ap, format);
	count = 0;
	i = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			count += ft_all_put(ap, format[i + 1]);
			i++;
		}
		else
			count += ft_putchar(format[i]);
		i++;
	}
	va_end(ap);
	return (count);
}
