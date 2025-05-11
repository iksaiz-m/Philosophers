/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 19:30:18 by iksaiz-m          #+#    #+#             */
/*   Updated: 2025/05/11 19:19:34 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	assign_fork(t_philo *philo, t_forks *fork, int position)
{
	int	philo_nbr;

	philo_nbr = philo->dinner->number_of_philosopher;
	if (philo->id % 2 == 0)
	{
		philo->left_fork = &fork[position];
		philo->right_fork = &fork[(position + 1) % philo_nbr];
	}
	else
	{
		philo->left_fork = &fork[(position + 1) % philo_nbr];
		philo->right_fork = &fork[position];
	}
}

static void	philo_init(t_table *dinner)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < dinner->number_of_philosopher)
	{
		philo = dinner->philos + i;
		philo->id = i + 1;
		philo->meals_eaten = 0;
		philo->full = false;
		philo->death = false;
		philo->dinner = dinner;
		philo->last_meal = get_time();
		pthread_mutex_init(&philo->last_meal_mutex, NULL);
		assign_fork(philo, dinner->forks, i);
	}
}

static int	init_mutex(t_table *dinner, int i)
{
	if (pthread_mutex_init(&dinner->lock, NULL) != 0)
		return (printf("Error creating the mutex \n"), 0);
	if (pthread_mutex_init(&dinner->write_mutex, NULL) != 0)
		return (printf("Error creating the mutex \n"), 0);
	if (pthread_mutex_init(&dinner->dead_mutex, NULL) != 0)
		return (printf("Error creating the mutex \n"), 0);
	while (++i < dinner->number_of_philosopher)
	{
		if (pthread_mutex_init(&dinner->forks[i].fork, NULL) != 0)
			return (printf("Error creating the mutex \n"), 0);
		dinner->forks[i].fork_id = i;
	}
	return (1);
}

int	init_table(t_table *dinner)
{
	int	i;

	i = -1;
	dinner->ending_flag = false;
	dinner->philos = malloc(sizeof(t_philo) * dinner->number_of_philosopher);
	if (!dinner->philos)
		return (0);
	dinner->forks = malloc(sizeof(t_forks) * dinner->number_of_philosopher);
	if (!dinner->forks)
		return (0);
	if (!init_mutex(dinner, -1))
		return (0);
	philo_init(dinner);
	return (1);
}

void	init_data(t_table *dinner, char **av)
{
	dinner->number_of_philosopher = ft_long_atoi(av[1]);
	dinner->time_to_die = ft_long_atoi(av[2]);
	dinner->time_to_eat = ft_long_atoi(av[3]);
	dinner->time_to_sleep = ft_long_atoi(av[4]);
	dinner->time_of_start = get_time();
	if (av[5])
		dinner->number_of_times_each_philosopher_must_eat = ft_long_atoi(av[5]);
	else
		dinner->number_of_times_each_philosopher_must_eat = -1;
}
