/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcakay <mcakay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 15:48:20 by mcakay            #+#    #+#             */
/*   Updated: 2022/08/22 18:22:02 by mcakay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_success(int signal)
{
	if (signal == SIGUSR1)
		ft_printf("Message sent successfully!");
}

char	*convert_bits(unsigned int c, int size, unsigned int a)
{
	char	*str;
	int		j;

	str = malloc(sizeof(char) * (size + 1));
	j = 0;
	while (a > 0)
	{
		if (c >= a)
		{
			*(str + j) = '1';
			c %= a;
		}
		else
			*(str + j) = '0';
		a /= 2;
		j++;
	}
	*(str + j) = '\0';
	return (str);
}

void	send_signal(int pid, unsigned int c, int size, unsigned int a)
{
	char	*bit;
	int		i;

	bit = convert_bits(c, size, a);
	i = 0;
	while (*(bit + i))
	{
		if (*(bit + i) == '1')
			kill(pid, SIGUSR1);
		else if (*(bit + i) == '0')
			kill(pid, SIGUSR2);
		usleep(100);
		i++;
	}
	free(bit);
}

void	send_signal_while(int pid, char *str, int size, unsigned int a)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(str);
	while (len >= 0)
	{
		send_signal(pid, str[i], size, a);
		len--;
		i++;
	}
}

int	main(int argc, char **argv)
{
	int		pid;
	int		client_pid;

	client_pid = getpid();
	signal(SIGUSR1, ft_success);
	if (argc != 3)
		return (1);
	pid = ft_atoi(argv[1]);
	if (pid < 0)
		return (1);
	send_signal(pid, client_pid, 32, 2147483648);
	send_signal_while(pid, argv[2], 8, 128);
	send_signal(pid, '\n', 8, 128);
	return (0);
}
