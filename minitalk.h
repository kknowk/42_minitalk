/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:31:57 by khorike           #+#    #+#             */
/*   Updated: 2023/06/16 18:04:35 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <unistd.h>
# include <string.h>
# include <stdarg.h>
# include <limits.h>

ssize_t			ft_putchar(char c);
ssize_t			ft_putstr(char *s);
ssize_t			ft_putnbr(int n);
ssize_t			ft_put_unsigned_nbr(unsigned int n);
ssize_t			ft_putnbr_base(long int n, int low_or_up);
ssize_t			ft_put_pointer(unsigned long long n);
size_t			ft_strlen(const char *s);

int				ft_printf(const char *format, ...);

#endif
