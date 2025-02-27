/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 20:05:39 by iksaiz-m          #+#    #+#             */
/*   Updated: 2025/01/20 20:09:31 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error2(void)
{
	printf("Error, introduce 4 or 5 positive numbers as arguments\n");
	printf("1: number_of_philosophers, 2: time_to_die, 3: time_to_eat");
	printf(", 4: time_to_sleep, ");
	printf("5: (optional) number_of_times_each_philosopher_must_eat\n");
	return ;
}

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (c);
	else
		return (0);
}

static int	check_argument(char *av)
{
	int	i;

	i = 0;
	if (av[0] == '\0')
		return (0);
	while (av[i] != '\0')
	{
		if (av[i] == '+')
		{
			i++;
			if (!ft_isdigit(av[i]) || av[i] == '-')
				return (0);
		}
		while (ft_isdigit(av[i]))
			i++;
		//if (av[i] != ' ' && av[i] != '	' && av[i] != '\0')
		if (av[i] != '\0')
			return (0);
		// while (av[i] == ' ' || av[i] == '	')
		// 	i++;
		if (av[i] == '\0')
			return (1);
	}
	return (1);
}

int	handle_multiple_arguments(int ac, char **av)
{
	int	i;

	i = 0;
	while (++i < ac)
	{
		if (!check_argument(av[i]))
			return (0);
	}
	return (1);
}

long	ft_long_atoi(const char *str)
{
	long	result;
	int		i;

	result = 0;
	i = 0;
	while ((str[i] == '\f' || str[i] == '\n' || str[i] == '\r'
			|| str[i] == '\t' || str[i] == '\v' || str[i] == ' '))
		i++;
	if (str[i] == '+')
		i++;
	while ((ft_isdigit(str[i])))
	{
		result = result * 10 +(str[i] - '0');
		i++;
	}
	return (result);
}
