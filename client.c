/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 12:55:34 by khorike           #+#    #+#             */
/*   Updated: 2023/06/21 12:18:11 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t	g_a = 1;

static int	ft_atoi_kai(char *nptr)
{
	int	i;
	int	digit;
	int	result;

	i = 0;
	digit = 0;
	result = 0;
	while (nptr[i])
	{
		digit = nptr[i] - '0';
		if (digit < 0 || digit > 9)
		{
			write(STDERR_FILENO, "digit error\n", 12);
			exit(EXIT_FAILURE);
		}
		if (result > INT_MAX / 10
			|| (result == INT_MAX / 10 && digit > INT_MAX % 10))
		{
			write(STDERR_FILENO, "overflow error\n", 15);
			exit(EXIT_FAILURE);
		}
		result = result * 10 + digit;
		i++;
	}
	return (result);
}

static void	send_signal(int pidserv, int bit)
{
	if (bit == 0)
	{
		usleep(1000);
		if (kill(pidserv, SIGUSR2) == -1)
		{
			write(STDERR_FILENO, "kill error\n", 11);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		usleep(1000);
		if (kill(pidserv, SIGUSR1) == -1)
		{
			write(STDERR_FILENO, "kill error\n", 11);
			exit(EXIT_FAILURE);
		}
	}
}

static void	receive_signal(int signum)
{
	if (signum == SIGUSR1)
		ft_printf("OK\n");
	else
		ft_printf("Fail!\n");
	g_a = 0;
}

static void	ft_send_src(char *s, int pidserv)
{
	int					i;
	unsigned char		letra;
	int					bit;
	int					current_bit;

	i = 0;
	current_bit = 0;
	while (s[i])
	{
		letra = s[i];
		bit = CHAR_BIT - 1;
		while (bit >= 0)
		{
			current_bit = (letra >> bit) & 1;
			send_signal(pidserv, current_bit);
			usleep(100);
			while (g_a)
				;
			g_a = 1;
			bit--;
		}
		i++;
	}
}

int	main(int ac, char *av[])
{
	struct sigaction	sa;
	pid_t				server_pid;

	if (ac != 3)
	{
		ft_printf("Usage: client <server_pid> <string>\n");
		return (EXIT_FAILURE);
	}
	server_pid = ft_atoi_kai(av[1]);
	sa.sa_handler = receive_signal;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
	{
		write(STDERR_FILENO, "sigaction\n", 10);
		return (EXIT_FAILURE);
	}
	ft_send_src(av[2], server_pid);
	ft_printf("finish string\n");
	return (EXIT_SUCCESS);
}
