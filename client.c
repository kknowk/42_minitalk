/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 12:55:34 by khorike           #+#    #+#             */
/*   Updated: 2023/06/16 18:17:40 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	atat(const char *nptr, int count)
{
	size_t	i;
	size_t	j;
	size_t	digit;

	i = 0;
	j = 0;
	while (nptr[i] && nptr[i] >= '0' && nptr[i] <= '9')
	{
		digit = nptr[i] - '0';
		j = j * 10 + digit;
		if (count == 1 && nptr[i + 1] >= '0' && nptr[i + 1] <= '9')
		{
			if ((j == LONG_MAX / 10 && nptr[i + 1] - '0' > LONG_MAX % 10)
				|| (j > LONG_MAX / 10 && nptr[i + 1]))
				return ((int)(LONG_MAX));
		}
		else if (count != 1 && nptr[i + 1] >= '0' && nptr[i + 1] <= '9')
		{
			if ((j == LONG_MAX / 10 && nptr[i + 1] - '0' > LONG_MAX % 10 + 1)
				|| (j > LONG_MAX / 10 && nptr[i + 1]))
				return ((int)(LONG_MIN));
		}
		i++;
	}
	return ((int)(j * count));
}

static int	ft_atoi(const char *nptr)
{
	int		i;
	int		j;
	int		count;

	i = 0;
	j = 0;
	count = 1;
	if (!nptr)
		return (0);
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if ((nptr[i] == '+') || (nptr[i] == '-'))
	{
		if (nptr[i] == '-')
			count *= -1;
		return (atat(nptr + i + 1, count));
	}
	return (atat(nptr + i, count));
}

void	ft_send_src(char *s, int pidserv)
{
	int		i;
	char	letra;
	int		bit;

	i = 0;
	while (s[i])
	{
		letra = s[i];
		bit = 7;
		while (bit >= 0)
		{
			if (letra & (1 << bit))
				kill(pidserv, SIGUSR1);
			else
				kill(pidserv, SIGUSR2);
			usleep(100);
			bit--;
		}
		i++;
	}
}

int	main(int ac, char *av[])
{
	pid_t	server_pid;

	if (ac != 3)
	{
		ft_printf("Usage: client <server_pid> <string>\n");
		return (1);
	}
	server_pid = ft_atoi(av[1]);
	ft_send_src(av[2], server_pid);
	return (0);
}
