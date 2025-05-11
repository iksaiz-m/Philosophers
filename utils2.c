/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 13:33:07 by iksaiz-m          #+#    #+#             */
/*   Updated: 2025/05/11 18:23:11 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < milliseconds)
		usleep(500);
	return (0);
}

bool	philo_is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->dinner->dead_mutex);
	if (philo->death == 1)
		return (pthread_mutex_unlock(&philo->dinner->dead_mutex), 1);
	pthread_mutex_unlock(&philo->dinner->dead_mutex);
	return (0);
}
