/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 19:32:20 by iksaiz-m          #+#    #+#             */
/*   Updated: 2025/05/11 19:20:36 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

long	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) != 0)
		return (printf("Time error!"));
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	write_status(t_philo *philo, char *str)
{
	long	timepass;

	pthread_mutex_lock(&philo->dinner->lock);
	if (philo->dinner->ending_flag != 0)
	{
		pthread_mutex_unlock(&philo->dinner->lock);
		return ;
	}
	pthread_mutex_unlock(&philo->dinner->lock);
	timepass = get_time() - philo->dinner->time_of_start;
	if (philo->full)
		return ;
	pthread_mutex_lock(&philo->dinner->write_mutex);
	printf("%ld %i %s\n", timepass, philo->id, str);
	pthread_mutex_unlock(&philo->dinner->write_mutex);
	return ;
}

bool	death_philo(t_philo *philo)
{
	long	latest_meal;

	if (philo->full == true)
		return (false);
	pthread_mutex_lock(&philo->last_meal_mutex);
	latest_meal = get_time() - philo->last_meal;
	if (latest_meal > philo->dinner->time_to_die)
	{
		philo->death = true;
		return (pthread_mutex_unlock(&philo->last_meal_mutex), true);
	}
	return (pthread_mutex_unlock(&philo->last_meal_mutex), false);
}
