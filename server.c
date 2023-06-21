/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 13:17:03 by khorike           #+#    #+#             */
/*   Updated: 2023/06/20 20:25:41 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	ft_bit_src(char *s)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	result;

	i = 0;
	while (s[i])
	{
		result = 0;
		j = 0;
		while (j < CHAR_BIT)
		{
			result = (result << 1) + (s[i + j] - '0');
			j++;
		}
		write(STDOUT_FILENO, &result, 1);
		i += CHAR_BIT;
	}
}

static void	ft_zero_or_one(int signum, siginfo_t *siginfo, void *context)
{
	static size_t	i;
	static char		c[CHAR_BIT];

	(void)context;
	if (signum == SIGUSR1)
		c[i] = '1';
	else if (signum == SIGUSR2)
		c[i] = '0';
	i++;
	if (i == CHAR_BIT)
	{
		i = 0;
		ft_bit_src(c);
	}
	usleep(800);
	if (kill(siginfo->si_pid, SIGUSR1) == -1)
	{
		write(STDERR_FILENO, "kill error\n", 11);
		exit(EXIT_FAILURE);
	}
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = ft_zero_or_one;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
	{
		write(STDERR_FILENO, "sigaction\n", 10);
		return (EXIT_FAILURE);
	}
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		write(STDERR_FILENO, "sigaction\n", 10);
		return (EXIT_FAILURE);
	}
	ft_printf("%d\n", getpid());
	while (1)
	{
		pause();
	}
	return (EXIT_SUCCESS);
}
