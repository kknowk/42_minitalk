/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 13:17:03 by khorike           #+#    #+#             */
/*   Updated: 2023/06/16 18:49:20 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_bit_src(char *s)
{
	int				i;
	int				j;
	unsigned int	result;

	i = 0;
	while (s[i])
	{
		result = 0;
		j = 0;
		while (j < 8)
		{
			result = (result << 1) + (s[i + j] - '0');
			j++;
		}
		write(1, &result, 1);
		i += 8;
	}
}

void	ft_zero_or_one(int signum)
{
	static int	i;
	static char	c[8];

	if (signum == SIGUSR1)
		c[i] = '1';
	else if (signum == SIGUSR2)
		c[i] = '0';
	i++;
	if (i == 8)
	{
		i = 0;
		ft_bit_src(c);
	}
}

int	main(void)
{
	ft_printf("%d\n", getpid());
	signal(SIGUSR1, ft_zero_or_one);
	signal(SIGUSR2, ft_zero_or_one);
	while (1)
	{
		sleep(1);
		pause();
	}
	return (0);
}
