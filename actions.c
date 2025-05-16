/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 20:34:02 by iksaiz-m          #+#    #+#             */
/*   Updated: 2025/05/16 20:15:13 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleep_action(t_philo *philo)
{
	pthread_mutex_lock(&philo->dinner->lock);
	if (philo->dinner->ending_flag != 0)
	{
		pthread_mutex_unlock(&philo->dinner->lock);
		return ;
	}
	pthread_mutex_unlock(&philo->dinner->lock);
	write_status(philo, "sleeping");
	ft_usleep(philo->dinner->time_to_sleep);
}

void	think_action(t_philo *philo)
{
	pthread_mutex_lock(&philo->dinner->lock);
	if (philo->dinner->ending_flag != 0)
	{
		pthread_mutex_unlock(&philo->dinner->lock);
		return ;
	}
	pthread_mutex_unlock(&philo->dinner->lock);
	write_status(philo, "thinking");
}

void	eat_action(t_philo *philo)
{
	pthread_mutex_lock(&philo->dinner->lock);
	if (philo->dinner->ending_flag != 0)
	{
		pthread_mutex_unlock(&philo->dinner->lock);
		return ;
	}
	pthread_mutex_unlock(&philo->dinner->lock);
	pthread_mutex_lock(&philo->left_fork->fork);
	write_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->right_fork->fork);
	write_status(philo, "has taken a fork");
	write_status(philo, "is eating");
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->meals_eaten += 1;
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->last_meal_mutex);
	ft_usleep(philo->dinner->time_to_eat);
	pthread_mutex_unlock(&philo->right_fork->fork);
	pthread_mutex_unlock(&philo->left_fork->fork);
	if (philo->meals_eaten
		== philo->dinner->number_of_times_each_philosopher_must_eat)
		philo->full = true;
}
