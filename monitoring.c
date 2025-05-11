/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 16:50:17 by iksaiz-m          #+#    #+#             */
/*   Updated: 2025/05/11 19:18:32 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	check_dead_philo(t_table *chef, int i)
{
	while (i < chef->number_of_philosopher)
	{
		if (death_philo(&chef->philos[i]))
		{
			write_status(&chef->philos[i], "died");
			pthread_mutex_lock(&chef->lock);
			chef->ending_flag = true;
			pthread_mutex_unlock(&chef->lock);
			return (chef->ending_flag);
		}
		i++;
	}
	return (false);
}

static bool	check_finished_eating(t_table *chef, int i, int all_full)
{
	while (i < chef->number_of_philosopher)
	{
		if (chef->philos[i].full == true)
			all_full++;
		i++;
	}
	if (all_full == chef->number_of_philosopher)
	{
		pthread_mutex_lock(&chef->lock);
		chef->ending_flag = true;
		pthread_mutex_unlock(&chef->lock);
		return (chef->ending_flag);
	}
	return (false);
}

bool	check_end_flag(t_table *chef, int i)
{
	if (check_dead_philo(chef, i))
		return (true);
	if (check_finished_eating(chef, i, 0))
		return (true);
	return (false);
}
