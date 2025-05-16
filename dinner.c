/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:07:20 by iksaiz-m          #+#    #+#             */
/*   Updated: 2025/05/16 20:00:41 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	one_philo_only(t_philo *philo)
{
	pthread_mutex_lock(&philo->dinner->forks->fork);
	write_status(&philo[0], "has taken a fork");
	pthread_mutex_unlock(&philo->dinner->forks->fork);
	ft_usleep(philo->dinner->time_to_die);
	write_status(&philo[0], "died");
}

void	*philorutine(void *dinners)
{
	t_philo	*philo;
	bool	end;

	philo = (t_philo *)dinners;
	while (1)
	{
		pthread_mutex_lock(&philo->dinner->lock);
		end = philo->dinner->ending_flag;
		pthread_mutex_unlock(&philo->dinner->lock);
		if (philo_is_dead(philo) || end)
			break ;
		eat_action(philo);
		sleep_action(philo);
		think_action(philo);
	}
	return (dinners);
}

void	*serve_food(void *chefs)
{
	t_table	*chef;
	int		i;

	i = 0;
	chef = (t_table *)chefs;
	while (1)
	{
		if (check_end_flag(chef, i))
			break ;
	}
	return (chefs);
}

int	init_thread(t_table *dinner)
{
	int	i;

	i = 0;
	if (dinner->number_of_times_each_philosopher_must_eat == 0)
		return (1);
	else if (dinner->number_of_philosopher == 1)
		return (one_philo_only(dinner->philos), 1);
	if (pthread_create(&dinner->chef, NULL, &serve_food, dinner) != 0)
		return (printf("Error creating the thread \n"),
			finish_dinner(dinner), 0);
	while (i < dinner->number_of_philosopher)
	{
		if (pthread_create(&dinner->philos[i].thread_id, NULL,
				&philorutine, &dinner->philos[i]) != 0)
			return (printf("Error creating the thread \n"),
				finish_dinner(dinner), 0);
		i++;
	}
	i = -1;
	pthread_join(dinner->chef, NULL);
	while (++i < dinner->number_of_philosopher)
		pthread_join(dinner->philos[i].thread_id, NULL);
	return (1);
}

int	main(int ac, char **av)
{
	t_table	dinner;

	if (ac < 5 || ac > 6 || !handle_multiple_arguments(ac, av))
	{
		error();
		return (1);
	}
	init_data(&dinner, av);
	if (!init_table(&dinner))
		return (1);
	if (!init_thread(&dinner))
		return (1);
	finish_dinner(&dinner);
	return (0);
}
