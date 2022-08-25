/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcakay <mcakay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 15:48:28 by mcakay            #+#    #+#             */
/*   Updated: 2022/08/22 17:53:49 by mcakay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

unsigned int	power_2(int power)
{
	unsigned int	x;

	x = 1;
	while (power)
	{
		x = x * 2;
		power--;
	}
	return (x);
}

void	pid_handler(int signal)
{
	static int			i;
	unsigned int		x;
	static unsigned int	result;

	x = 2147483648 / power_2(i);
	if (signal == SIGUSR1)
		result += x;
	i++;
	if (x == 1)
	{		
		kill(result, SIGUSR1);
		i = 0;
		result = 0;
	}
}

void	handler(int signal)
{
	static int	i;
	static int	j;
	static int	result;
	int			x;

	if (j < 32)
	{
		pid_handler(signal);
		j++;
		return ;
	}
	x = 128 / power_2(i);
	if (signal == SIGUSR1)
		result += x;
	i++;
	if (x == 1)
	{		
		if (result == '\n')
			j = 0;
		ft_printf("%c", result);
		i = 0;
		result = 0;
	}
}

int	main(void)
{
	int			pid;

	pid = getpid();
	ft_printf("pid: %d\n", pid);
	signal(SIGUSR1, handler);
	signal(SIGUSR2, handler);
	while (1)
		pause();
	return (0);
}
