/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conversions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 14:59:08 by khorike           #+#    #+#             */
/*   Updated: 2023/06/18 14:32:56 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

ssize_t	ft_putchar(char c)
{
	ssize_t	num;

	num = 0;
	num = write(1, &c, 1);
	return (num);
}

ssize_t	ft_putstr(char *s)
{
	size_t	i;
	ssize_t	num;

	i = 0;
	num = 0;
	if (!s)
	{
		num = write(1, "(null)", 6);
		return (num);
	}
	num = write(1, &s[i], ft_strlen(s));
	return (num);
}

ssize_t	ft_putnbr(int n)
{
	ssize_t	num;

	num = 0;
	if (n == -2147483648)
	{
		num = write(1, "-2147483648", 11);
		return (num);
	}
	else if (n < 0)
	{
		num = write(1, "-", 1);
		n = -n;
	}
	if (n >= 10)
		num += ft_putnbr(n / 10);
	num += write(1, &"0123456789"[n % 10], 1);
	return (num);
}

ssize_t	ft_put_unsigned_nbr(unsigned int n)
{
	ssize_t	num;

	num = 0;
	if (n >= 10)
		num += ft_put_unsigned_nbr(n / 10);
	num += write(1, &"0123456789"[n % 10], 1);
	return (num);
}

ssize_t	ft_putnbr_base(long int n, int low_or_up)
{
	ssize_t		num;
	const char	low[] = "0123456789abcdef";
	const char	up[] = "0123456789ABCDEF";

	num = 0;
	if (low_or_up == 0)
	{
		if (n >= 16)
			num += ft_putnbr_base(n / 16, 0);
		num += write(1, &low[n % 16], 1);
	}
	else if (low_or_up == 1)
	{
		if (n >= 16)
			num += ft_putnbr_base(n / 16, 1);
		num += write(1, &up[n % 16], 1);
	}
	return (num);
}
