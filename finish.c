/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 22:54:02 by iksaiz-m          #+#    #+#             */
/*   Updated: 2025/05/11 19:19:56 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	finish_dinner(t_table *dinner)
{
	int	i;

	i = -1;
	pthread_mutex_destroy(&dinner->lock);
	pthread_mutex_destroy(&dinner->philos->last_meal_mutex);
	pthread_mutex_destroy(&dinner->write_mutex);
	pthread_mutex_destroy(&dinner->dead_mutex);
	while (++i < dinner->number_of_philosopher)
		pthread_mutex_destroy(&dinner->forks[i].fork);
	free(dinner->philos);
	free(dinner->forks);
}
